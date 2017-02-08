#include "cma_optimizer.hpp"

namespace flut
{
	cma_optimizer::cma_optimizer( int dim, const real_vec& init_mean, const real_vec& init_std, objective_func_t func, cma_weights w ) :
	optimizer( dim, func )
	{ }

	cma_optimizer::cma_optimizer( int dim, const real_vec& init_mean, const real_vec& init_std, const real_vec& lower_bounds, const real_vec& upper_bounds, objective_func_t func, cma_weights w ) :
	optimizer( dim, lower_bounds, upper_bounds, func )
	{ }
}
