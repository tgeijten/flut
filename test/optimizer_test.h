#pragma once

#include "flut/system/test_framework.hpp"
#include "c-cmaes/cmaes_interface.h"
#include "flut/optimizer/cma_optimizer.hpp"

/* the objective (fitness) function to be minimized */
inline double fitfun( double const *x, int N ) { /* function "cigtab" */
	int i;
	double sum = 1e4*x[ 0 ] * x[ 0 ] + 1e-4*x[ 1 ] * x[ 1 ];
	for ( i = 2; i < N; ++i )
		sum += x[ i ] * x[ i ];
	return sum;
}

namespace flut
{
	void optimizer_test()
	{
		// setup mean / std / N
		int dim = 10;
		int seed = 123;
		int lambda = 0;
		std::vector< double > init_mean( dim, 0.0 );
		std::vector< double > init_std( dim, 0.3 );

		// init c-cmaes
		cmaes_t evo;
		double *arFunvals = cmaes_init( &evo, dim, &init_mean[ 0 ], &init_std[ 0 ], seed, lambda, "no" );

		// init cma_optimizer
		cma_optimizer cma( dim, init_mean, init_std, lambda, seed );

		/* Iterate until stop criterion holds */
		for ( int gen = 0; gen < 100; ++gen )
		{
			// update C-CMAES
			{
				/* generate lambda new search points, sample population */
				double* const* pop;
				printf( "C%03d: ", gen );
				pop = cmaes_SamplePopulation( &evo ); /* do not change content of pop */

				/* evaluate the new search points using fitfun */
				for ( int i = 0; i < cmaes_Get( &evo, "lambda" ); ++i ) {
					arFunvals[ i ] = fitfun( pop[ i ], (int)cmaes_Get( &evo, "dim" ) );
					printf( "%.2f ", arFunvals[ i ] );
				}

				/* update the search distribution used for cmaes_SamplePopulation() */
				cmaes_UpdateDistribution( &evo, arFunvals );
				printf( "\n" );
			}

			// update cma_optimizer
			{
				printf( "D%03d: ", gen );
				auto& cma_pop = cma.sample_population();
				std::vector< double > cma_results( dim );
				for ( int i = 0; i < cma.lambda(); ++i ) {
					cma_results[ i ] = fitfun( &cma_pop[ i ][ 0 ], dim );
					printf( "%.2f ", cma_results[ i ] );
				}

				/* update the search distribution used for cmaes_SamplePopulation() */
				cma.update_distribution( cma_results );
				printf( "\n" );
			}
		}

		/* get best estimator for the optimum, xmean */
		double* xfinal = cmaes_GetNew( &evo, "xmean" ); /* "xbestever" might be used as well */
		cmaes_exit( &evo ); /* release memory */

		/* do something with final solution and finally release memory */
		free( xfinal );
	}
}
