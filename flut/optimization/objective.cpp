#include "objective.hpp"

#include "flut/math/math.hpp"

namespace flut
{
	bool objective::is_better( fitness_t a, fitness_t b ) const
	{
		return minimize() ? a < b : a > b;
	}

	flut::fitness_t objective::worst_fitness() const
	{
		return minimize() ? math::numeric_const< fitness_t >::max() : math::numeric_const< fitness_t >::lowest();
	}

	function_objective::function_objective( size_t d, function_t func, bool minimize, const vector< par_mean_std >& init, const vector< par_bounds >& b ) :
		dim_( d ),
		func_( func ),
		minimize_( minimize ),
		init_( init ),
		bounds_( b )
	{}
}
