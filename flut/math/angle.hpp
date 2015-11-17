#pragma once

#include <cmath>
#include "math.hpp"
#include "result_type.hpp"

namespace flut
{
	namespace math
	{
		// angles with units
		enum angle_unit { degrees, radians };
		template< angle_unit U, typename T >
		struct angle
		{
			T value;
			explicit angle( T v ) : value( v ) {}
			T rad() const;
			T deg() const;
		};

		template< angle_unit U, typename T1, typename T2 >
		angle< U, flut_result( T1, T2 ) > operator+( const angle< U, T1 >& a1, const angle< U, T2 >& a2 )
		{ return angle< U, flut_result( T1, T2 ) >( a1.value + a2.value ); }

		// angles that are actually always radians
		template< typename T >
		struct radian_
		{
			const T& rad() const { return value; }
			T deg() const { return rad_to_deg( value ); }

			static radian_<T> make_from_rad( T rad ) { return radian_<T>( rad ); }
			static radian_<T> make_from_deg( T deg ) { return radian_<T>( deg_to_rad( deg ) ); }

		private:
			explicit radian_( T v ) : value( v ) {}
			T value;
		};

		//template< typename T > angle_<T> rad( T rad ) { return angle_<T>::make_from_rad( rad ); }
		//template< typename T > angle_<T> deg( T deg ) { return angle_<T>::make_from_deg( deg ); }

		template< typename T, typename U >
		radian_< flut_result( T, U ) > operator+( const radian_< T >& a1, const radian_< U >& a2 )
		{ return radian_< flut_result( T, U ) >::make_from_rad( a1.rad() + a2.rad() ); }

		//template< typename T, typename U >
		//auto operator+( const angle_< T >& a1, const angle_< U >& a2 ) -> angle_< decltype( T(1) + U(1) ) >
		//{ return angle_< decltype( T(1) + U(1) ) >::make_from_rad( a1.rad() + a2.rad() ); }

		//template< typename T > T sin( const angle_< T >& a ) { return std::sin( a.rad() ); }
		//template< typename T > T cos( const angle_< T >& a ) { return std::cos( a.rad() ); }
		//template< typename T > T tan( const angle_< T >& a ) { return std::tan( a.rad() ); }
		//template< typename T > T asin( const angle_< T >& a ) { return std::asin( a.rad() ); }
		//template< typename T > T acos( const angle_< T >& a ) { return std::acos( a.rad() ); }
		//template< typename T > T atan( const angle_< T >& a ) { return std::atan( a.rad() ); }
	}
}
