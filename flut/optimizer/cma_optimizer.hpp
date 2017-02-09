#pragma once

#include "optimizer.hpp"

struct pimpl_t;

namespace flut
{
	enum class cma_weights { none = 0, equal = 1, linear = 2, super_linear = 3 };

	class FLUT_API cma_optimizer : public optimizer
	{
	public:

		cma_optimizer( int dim,
			const real_vec& init_mean, const real_vec& init_std,
			int lambda = 0, int seed = 123,
			cma_weights w = cma_weights::super_linear );

		cma_optimizer( int dim,
			const real_vec& init_mean, const real_vec& init_std,
			const real_vec& lower_bounds, const real_vec& upper_bounds,
			objective_func_t func, cma_weights w = cma_weights::super_linear );

		virtual ~cma_optimizer();

		const std::vector< std::vector< double > >& sample_population();
		void update_distribution( const std::vector< double >& results );

		int lambda() { return lambda_; }

	protected:
		int mu_;
		int lambda_;
		pimpl_t* pimpl;
	};
}
