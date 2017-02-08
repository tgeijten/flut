#include "optimizer.hpp"

namespace flut
{

	optimizer::optimizer( int d, objective_func_t f ) :
	dim( d ),
	func( f ),
	lower_bounds( dim, std::numeric_limits< real_t >::lowest() ),
	upper_bounds( dim, std::numeric_limits< real_t >::max() )
	{
	}

	optimizer::optimizer( int d, const real_vec& lower, const real_vec& upper, objective_func_t f ) :
	dim( d ),
	func( f ),
	lower_bounds( lower ),
	upper_bounds( upper )
	{
	}

	optimizer::~optimizer()
	{
	}

	optimizer::real_vec optimizer::evaluate( const vector< real_vec >& pop )
	{
		real_vec fitness;
		fitness.reserve( dim );
		for ( auto& ind : pop )
			fitness.push_back( func( ind ) );
		return fitness;
	}

	void optimizer::to_bounded( real_vec& values )
	{
	}

	void optimizer::from_bounded( real_vec& values )
	{
	}
}

