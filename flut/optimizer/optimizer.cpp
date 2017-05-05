#include "optimizer.hpp"
#include <future>
#include "flut/system/log.hpp"
#include <xfunctional>

namespace flut
{
	no_objective optimizer::no_objective_;


	optimizer::optimizer( const objective& o ) :
	objective_( o )
	{ }

	optimizer::~optimizer()
	{
	}

	fitness_vec_t optimizer::evaluate( const vector< param_vec_t >& pop )
	{
		vector< double > results( pop.size(), 0.0 );

		try
		{
			vector< std::pair< std::future< double >, index_t > > threads;

			for ( index_t eval_idx = 0; eval_idx < pop.size(); ++eval_idx )
			{
				// first make sure enough threads are available
				while ( threads.size() >= max_threads() )
				{
					for ( auto it = threads.begin(); it != threads.end(); )
					{
						if ( it->first.wait_for( std::chrono::milliseconds( 1 ) ) == std::future_status::ready )
						{
							// a thread is finished, lets add it to the results and make room for a new thread
							results[ it->second ] = it->first.get();
							it = threads.erase( it );
						}
						else ++it;
					}
				}

				// add new thread
				threads.push_back( std::make_pair( std::async( std::launch::async, [&]( const param_vec_t& p ) { return objective_.evaluate( p ); }, pop[ eval_idx ] ), eval_idx ) );
			}

			// wait for remaining threads
			for ( auto& f : threads )
				results[ f.second ] = f.first.get();
		}
		catch ( std::exception& e )
		{
			log::critical( "Error during multi-threaded evaluation: ", e.what() );
		}

		return results;
	}
}
