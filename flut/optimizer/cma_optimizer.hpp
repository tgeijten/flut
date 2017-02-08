#pragma once

#include "optimizer.hpp"

namespace flut
{
	enum class cma_weights { none = 0, equal = 1, linear = 2, super_linear = 3 };

	class cma_optimizer : public optimizer
	{
	public:

		cma_optimizer( int dim,
			const real_vec& init_mean, const real_vec& init_std,
			objective_func_t func, cma_weights w = cma_weights::super_linear );

		cma_optimizer( int dim,
			const real_vec& init_mean, const real_vec& init_std,
			const real_vec& lower_bounds, const real_vec& upper_bounds,
			objective_func_t func, cma_weights w = cma_weights::super_linear );

		virtual ~cma_optimizer() {}
		
	protected:
		int mu;
		int lambda;
	};
}
