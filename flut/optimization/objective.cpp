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

	function_objective::function_objective( size_t d, function_t func, bool minimize, const par_vec& start, const par_vec& start_std, const par_vec& upper, const par_vec& lower ) :
	func_( func ),
	minimize_( minimize )
	{
		// create par_info
		for ( size_t i = 0; i < d; ++i )
			par_info_.push_back( stringf( "%d", i ), start[ i ], start_std[ i ], i < lower.size() ? lower[ i ] : -1e15, i < lower.size() ? lower[ i ] : 1e15 );
	}
}
