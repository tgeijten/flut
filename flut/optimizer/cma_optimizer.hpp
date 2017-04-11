#pragma once

#include "optimizer.hpp"

namespace flut
{
	enum class cma_weights { equal = 0, linear = 1, log = 2 };

	class FLUT_API cma_optimizer : public optimizer
	{
	public:

		cma_optimizer( int dim,
			const search_point_t& init_mean, const search_point_t& init_std,
			objective_func_t func = optimizer::no_objective_func,
			int lambda = 0, int seed = 123,
			cma_weights w = cma_weights::log );

		cma_optimizer( int dim,
			const search_point_t& init_mean, const search_point_t& init_std,
			const search_point_t& lower_bounds, const search_point_t& upper_bounds,
			objective_func_t func = optimizer::no_objective_func,
			int lambda = 0, int seed = 123,
			cma_weights w = cma_weights::log );

		virtual ~cma_optimizer();

		void set_boundaries( const vector< double >& lower, const vector< double >& upper );

		const vector< vector< double > >& sample_population();
		void update_distribution( const std::vector< double >& results );

		search_point_t current_mean() const;
		search_point_t current_std() const;
		const vector< search_point_t >& current_pop() const;

		int lambda() const;
		int mu() const;
		int dim() const;
		int random_seed() const;
		double sigma() const;

	protected:
		struct pimpl_t* pimpl;
	};
}
