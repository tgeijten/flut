#include "optimizer.hpp"
#include <future>
#include "flut/system/log.hpp"
#include <cmath>

namespace flut
{
	optimizer::optimizer( const objective& o ) :
	objective_( o ),
	current_fitness_( o.worst_fitness() )
	{}

	optimizer::~optimizer()
	{}

	bool optimizer::test_stop_condition( const stop_condition& stop ) const
	{
		if ( current_generation() >= stop.max_generations )
			return true;

		if ( !std::isnan( stop.fitness ) && objective_.is_better( current_fitness(), stop.fitness ) )
			return true;

		// none of the criteria is met -> return false
		return false;
	}

	fitness_vec_t optimizer::evaluate( const vector< par_vec >& pop )
	{
		vector< double > results( pop.size(), objective_.worst_fitness() );
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
							it = threads.erase( it );
						}
						else ++it;
					}
				}

				// add new thread
				threads.push_back( std::make_pair( std::async( std::launch::async, [&]( const par_vec& p ) { return objective_.evaluate( p ); }, pop[ eval_idx ] ), eval_idx ) );
			}

			// wait for remaining threads
			for ( auto& f : threads )
				results[ f.second ] = f.first.valid() ? f.first.get() : objective_.worst_fitness();
		}
		catch ( std::exception& e )
		{
			log::critical( "Error during multi-threaded evaluation: ", e.what() );
		}

		return results;
	}
}
