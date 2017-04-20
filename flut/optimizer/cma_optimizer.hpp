#pragma once

#include "optimizer.hpp"

namespace flut
{
	enum class cma_weights { equal = 0, linear = 1, log = 2 };

	class FLUT_API cma_optimizer : public optimizer
	{
	public:

		cma_optimizer( int dim, objective_func_t func,
			const search_point_t& init_mean, const search_point_t& init_std,
			int lambda = 0, int seed = 123,
			cma_weights w = cma_weights::log );

		cma_optimizer( int dim, objective_func_t func,
			const search_point_t& init_mean, const search_point_t& init_std,
			const search_point_t& lower_bounds, const search_point_t& upper_bounds,
			int lambda = 0, int seed = 123,
			cma_weights w = cma_weights::log );

		virtual ~cma_optimizer();

		// initialization
		void set_boundaries( const vector< double >& lower, const vector< double >& upper );
		//void set_objective( const objective_func_t& f );
		//void set_random_seed( int seed );
		//void set_weights( cma_weights w );
		//void set_lambda_mu( int lambda, int mu = 0 );
		//void set_init_mean_std( const search_point_t& mean, const search_point_t& std );

		// optimization
		const vector< vector< double > >& sample_population();
		void update_distribution( const std::vector< double >& results );

		// analysis
		search_point_t current_mean() const;
		search_point_t current_std() const;
		const vector< search_point_t >& current_pop() const;

		// actual parameters
		int dim() const;
		int lambda() const;
		int mu() const;
		int random_seed() const;
		double sigma() const;

	protected:
		struct pimpl_t* pimpl;
	};
}
