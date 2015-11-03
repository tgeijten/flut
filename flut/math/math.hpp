#pragma once

#include "../types.hpp"
#include <limits>

namespace flut
{
	namespace math
	{
		/// math constants
		template< typename T = real_t > struct constants
		{
			static T pi() { return T( 3.14159265358979 ); }
			static T half_pi() { return T( 0.5 * 3.14159265358979 ); }
			static T two_pi() { return T( 2.0 * 3.14159265358979 ); }
			static T epsilon() { return std::numeric_limits< T >::epsilon(); }
			static T relaxed_epsilon() { return 4 * std::numeric_limits< T >::epsilon(); }
			static T one() { return T( 1 ); }
			static T zero() { return T( 0 ); }
		};

		/// handy functions
		template< typename T > T rad_to_deg( T rad_value ) { return ( T( 180 ) / constants<T>::pi() ) * rad_value; }
		template< typename T > T deg_to_rad( T deg_value ) { return ( constants<T>::pi() / T( 180 ) ) * deg_value; }
		template< typename T > bool equals( T v1, T v2, T e = constants<T>::relaxed_epsilon() ) { return abs( v1 - v2 ) <= abs( v1 ) * e; }
		template< typename T > T inv( T v ) { return T( 1 ) / v; }
		template< typename T > T invsqrt( T v ) { return T( 1 ) / sqrt( v ); }

		/// degrees and radians
		struct degree;
		struct radian
		{
			explicit radian( real_t v = 0.0 ) : value( v ) {}
			explicit radian( degree v );
			real_t value;
		};
		struct degree
		{
			explicit degree( real_t v = 0.0 ) : value( v ) {}
			explicit degree( const radian& v ) : value( rad_to_deg( v.value ) ) {}
			real_t value;
		};
		radian::radian( degree v ) : value( deg_to_rad( v.value ) ) {}
	}
}
