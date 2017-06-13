#include "optimizer.hpp"
#include <future>
#include "flut/system/log.hpp"
#include <cmath>
#include "flut/system_tools.hpp"

namespace flut
{
	optimizer::optimizer( const objective& o ) :
	objective_( o ),
	current_fitness_( o.info().worst_fitness() ),
	step_count_( 0 )
	{}

	optimizer::~optimizer()
	{
		abort_and_wait();
	}

	void optimizer::optimize_background()
	{
		abort_flag_ = false;
		background_thread = std::thread( [this]() { flut::set_thread_priority( thread_priority ); this->run(); } );
	}

	flut::optimizer::stop_condition optimizer::run( const stop_condition_info& stop )
	{
		for ( auto cb : callbacks_ )
			cb->start_cb( *this );

		for ( step_count_ = 0; test_stop_condition( stop ) == no_stop_condition; ++step_count_ )
		{
			for ( auto cb : callbacks_ )
				cb->next_generation_cb( step_count_ );

			step( stop );
		}

		for ( auto cb : callbacks_ )
			cb->finish_cb( *this );

		return test_stop_condition( stop );
	}

	void optimizer::abort_and_wait()
	{
		if ( background_thread.joinable() )
		{
			signal_abort();
			background_thread.join();
		}
	}

	optimizer::stop_condition optimizer::test_stop_condition( const stop_condition_info& stop ) const
	{
		// TODO: make this function virtual and keep internal state
		if ( test_abort() )
			return user_abort;

		if ( generation_count() >= stop.max_generations )
			return max_generations_reached;

		if ( stop.target_fitness && objective_.info().is_better( current_fitness(), *stop.target_fitness ) )
			return target_fitness_reached;

		// none of the criteria is met -> return false
		return no_stop_condition;
	}

	fitness_vec_t optimizer::evaluate( const search_point_vec& pop )
	{
		vector< double > results( pop.size(), objective_.info().worst_fitness() );
		try
		{
			vector< std::pair< std::future< double >, index_t > > threads;

			for ( index_t eval_idx = 0; eval_idx < pop.size(); ++eval_idx )
			{
				if ( abort_flag_.load() )
					break;

				// first make sure enough threads are available
				while ( threads.size() >= max_threads() )
				{
					for ( auto it = threads.begin(); it != threads.end(); )
					{
						if ( it->first.wait_for( std::chrono::milliseconds( 1 ) ) == std::future_status::ready )
						{
							// a thread is finished, add it to the results and make room for a new thread
							results[ it->second ] = it->first.get();

							// run callbacks
							for ( auto cb : callbacks_ )
								cb->evaluate_cb( pop[ it->second ], results[ it->second ] );

							it = threads.erase( it );
						}
						else ++it;
					}
				}

				// add new thread
				threads.push_back( std::make_pair( std::async( std::launch::async, [&]( const search_point& p ) { return objective_.evaluate( p ); }, pop[ eval_idx ] ), eval_idx ) );
			}

			// wait for remaining threads
			for ( auto& f : threads )
			{
				results[ f.second ] = f.first.valid() ? f.first.get() : objective_.info().worst_fitness();

				// run callbacks
				for ( auto cb : callbacks_ )
					cb->evaluate_cb( pop[ f.second ], results[ f.second ] );
			}

			// run callbacks
			for ( auto cb : callbacks_ )
				cb->evaluate_cb( pop, results );

			auto best_idx = objective_.info().find_best_fitness( results );
			if ( results[ best_idx ] > current_fitness_ )
			{
				current_fitness_ = results[ best_idx ];
				for ( auto cb : callbacks_ )
					cb->new_best_cb( pop[ best_idx ], results[ best_idx ] );
			}
		}
		catch ( std::exception& e )
		{
			log::critical( "Error during multi-threaded evaluation: ", e.what() );
		}

		return results;
	}
}
