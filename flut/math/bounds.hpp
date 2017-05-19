#pragma once
#include "math.hpp"

namespace flut
{
	template< typename T >
	class bounds
	{
	public:
		bounds( const T& upper_bound = math::numeric_const< T >::max(), const T& lower_bound = math::numeric_const< T >::lowest() ) : lower( lower ), upper( upper ) {};
		bounds( const prop_node& props );

		bool is_within( const T& value ) { return ( value >= lower ) && ( value <= upper ); }

		/// returns negative when value is below lower, positive when value is above upper, 0 when within bounds
		T get_violation( const T& value )
		{ if ( value < lower ) return value - lower; else if ( value > upper ) return value - upper; else return T( 0 ); }

		T& clamp( T& value ) { math::clamp( value, lower, upper ); return value; }
		T& soft_clamp( T& value, const T& boundary ) { math::soft_clamped( value, lower, upper, boundary ); return value; }

		T lower;
		T upper;
	};

	using boundsf = bounds< float >;
	using boundsd = bounds< double >;
	using boundsi = bounds< int >;

	template< typename T >
	flut::bounds<T>::bounds( const prop_node& props ) {
		lower = props.get_any< T >( { "min", "lower" }, numeric_const<T>::lowest() );
		upper = props.get_any<T>( { "max", "upper" }, numeric_const< T >::max() );
	}
}
