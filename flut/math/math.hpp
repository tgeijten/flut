#pragma once

#include "flut/system/types.hpp"
#include <limits>

namespace flut
{
	namespace math
	{
		/// constants
		template< typename T = real_t > struct constants
		{
			static T pi() { return T( 3.14159265358979 ); }
			static T half_pi() { return T( 0.5 * 3.14159265358979 ); }
			static T two_pi() { return T( 2 * 3.14159265358979 ); }
			static T epsilon() { return std::numeric_limits< T >::epsilon(); }
			static T relaxed_epsilon() { return T( 4 * std::numeric_limits< T >::epsilon() ); }
			static T one() { return T( 1 ); }
			static T zero() { return T( 0 ); }
		};
		const real_t real_pi = constants< real_t >::pi();

		/// convert rad to deg
		template< typename T > T rad_to_deg( T rad_value ) { return ( T( 180 ) / constants<T>::pi() ) * rad_value; }

		/// convert deg to rad
		template< typename T > T deg_to_rad( T deg_value ) { return ( constants<T>::pi() / T( 180 ) ) * deg_value; }

		/// compare floating point variables using relaxed_epsilon
		template< typename T > bool equals( T v1, T v2, T e = constants<T>::relaxed_epsilon() ) { return std::abs( v1 - v2 ) <= std::abs( v1 ) * e; }

		/// inverse of v (1 / v)
		template< typename T > T inv( T v ) { return T(1) / v; }

		/// inverse of sqrt
		template< typename T > T invsqrt( T v ) { return T(1) / sqrt( v ); }

		/// sign of v: 1 or -1
		template< typename T > T sign( T v ) { return v >= T(0) ? T(1) : T(-1); }

		/// return clamped value that is >= min and <= max
		template< typename T > T clamped( T v, T min, T max )
		{ if ( v < min ) return min; else if ( v > max ) return max; else return v; }

		/// clamp a value so that min <= v <= max
		template< typename T > void clamp( T& v, const T& min, const T& max )
		{ if ( v < min ) v = min; else if ( v > max ) v = max; return v; } /// TODO: use efficient instructions instead of relying on the compiler for optimization

		/// check if an integer value is a power of two
		template< typename T > T is_power_of_two( T v ) { return v != 0 && !( v & ( v - 1 ) ); }
	}
}
