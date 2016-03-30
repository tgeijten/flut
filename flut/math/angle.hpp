#pragma once

#include <cmath>
#include "math.hpp"
#include "result_type.hpp"

namespace flut
{
	namespace math
	{
		template< typename T >
		struct angle_
		{
			const T& rad() const { return value; }
			T deg() const { return rad_to_deg( value ); }

			static angle_<T> make_from_rad( const T& value ) { return angle_<T>( value ); }
			static angle_<T> make_from_deg( const T& value ) { return angle_<T>( deg_to_rad( value ) ); }

		private:
			explicit angle_( T v ) : value( v ) {}
			T value;
		};

		using angle = angle_< real_t >;
		using anglef = angle_< float >;
		using angled = angle_< double >;

		template< typename T > angle_<T> rad( T rad ) { return angle_<T>::make_from_rad( rad ); }
		template< typename T > angle_<T> deg( T deg ) { return angle_<T>::make_from_deg( deg ); }

		/// scalar multiplication
		template< typename T > angle_<T> operator*( const T& s, const angle_<T>& a )
		{ return angle_<T>::make_from_rad( s * a.rad() ); }
		template< typename T > angle_<T> operator*( const angle_<T>& a, const T& s )
		{ return angle_<T>::make_from_rad( s * a.rad() ); }

		template< typename T > angle_<T> operator+( const angle_<T>& a1, const angle_<T>& a2 )
		{ return angle_<T>::make_from_rad( a1.rad() + a2.rad() ); }

		template< typename T > angle_<T> operator-( const angle_<T>& a1, const angle_<T>& a2 )
		{ return angle_<T>::make_from_rad( a1.rad() - a2.rad() ); }

		template< typename T > T sin( const angle_< T >& a ) { return std::sin( a.rad() ); }
		template< typename T > T cos( const angle_< T >& a ) { return std::cos( a.rad() ); }
		template< typename T > T tan( const angle_< T >& a ) { return std::tan( a.rad() ); }
		template< typename T > T asin( const angle_< T >& a ) { return std::asin( a.rad() ); }
		template< typename T > T acos( const angle_< T >& a ) { return std::acos( a.rad() ); }
		template< typename T > T atan( const angle_< T >& a ) { return std::atan( a.rad() ); }
	}
}
