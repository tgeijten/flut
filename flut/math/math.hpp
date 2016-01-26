#pragma once

#include "../types.hpp"
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
		template< typename T > bool equals( T v1, T v2, T e = constants<T>::relaxed_epsilon() ) { return abs( v1 - v2 ) <= abs( v1 ) * e; }
		template< typename T > T inv( T v ) { return T( 1 ) / v; }
		template< typename T > T invsqrt( T v ) { return T( 1 ) / sqrt( v ); }
		template< typename T > T sign( T v ) { return v >= T(0) ? T(1) : T(-1); }

		/// check if an integer value is a power of two
		template< typename T > T is_power_of_two( T v ) { return v != 0 && !( v & ( v - 1 ) ); }

		/// number struct
		template< typename T > struct number_
		{
			T value;
			number_<T> operator*( number_<T> o ) const { return value * o.value; }
			number_<T> operator/( number_<T> o ) const { return value / o.value; }
		protected: // constructor is protected and should only by used by derived types
			number_( T v ) : value( v ) {}
		};

		/// degrees and radians
		struct degree;
		struct radian : public number_<real_t>
		{
			explicit radian( real_t v = 0.0 ) : number_<real_t>( v ) {}
			explicit radian( degree v );
			radian operator+( radian o ) const { return radian( value + o.value ); }
			radian operator-( radian o ) const { return radian( value - o.value ); }
		};
		struct degree : public number_<real_t>
		{
			explicit degree( real_t v = 0.0 ) : number_<real_t>( v ) {}
			explicit degree( const radian& v ) : number_<real_t>( rad_to_deg( v.value ) ) {}
			degree operator+( degree o ) const { return degree( value + o.value ); }
			degree operator-( degree o ) const { return degree( value - o.value ); }
		};
		inline radian::radian( degree v ) : number_<real_t>( deg_to_rad( v.value ) ) {}
	}
}
