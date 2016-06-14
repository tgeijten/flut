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

		/// handy functions
		template< typename T > T rad_to_deg( T rad_value ) { return ( T( 180 ) / constants<T>::pi() ) * rad_value; }
		template< typename T > T deg_to_rad( T deg_value ) { return ( constants<T>::pi() / T( 180 ) ) * deg_value; }
		template< typename T > bool equals( T v1, T v2, T e = constants<T>::relaxed_epsilon() ) { return std::abs( v1 - v2 ) <= std::abs( v1 ) * e; }
		template< typename T > T inv( T v ) { return T( 1 ) / v; }
		template< typename T > T invsqrt( T v ) { return T( 1 ) / sqrt( v ); }
		template< typename T > T sign( T v ) { return v >= T(0) ? T(1) : T(-1); }
		template< typename T > T between( T v, T min, T max ) { if ( v < min ) return min; else if ( v > max ) return max; else return v; }
		template< typename T > void limit( T& v, const T& min, const T& max ) {
			/// TODO: use efficient instructions instead of relying on the compiler for optimization
			if ( v < min ) v = min;
			else if ( v > max ) v = max;
			return v;
		}

		/// check if an integer value is a power of two
		template< typename T > T is_power_of_two( T v ) { return v != 0 && !( v & ( v - 1 ) ); }
	}
}
