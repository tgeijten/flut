#pragma once

#include <cmath>
#include "math.hpp"
#include "result_type.hpp"
#include "flut/system/assert.hpp"

namespace flut
{
	namespace math
	{
		enum class angle_unit { degrees, radians };

		template< angle_unit U, typename T >
		struct angle_ { };

		template< typename T >
		struct angle_< angle_unit::degrees, T >
		{
			angle_( const angle_< angle_unit::degrees, T >& a ) : value( a.value  ) {}
			angle_( const angle_< angle_unit::radians, T >& a ) : value( rad_to_deg( a.value ) ) {}
			static angle_< angle_unit::degrees, T > make( const T& value ) { return angle_< angle_unit::degrees, T >( value ); }
			T value;

		private:
			explicit angle_( const T& v ) : value( v ) {}
		};

		template< typename T >
		struct angle_< angle_unit::radians, T >
		{
			angle_( const angle_< angle_unit::radians, T >& a ) : value( a.value ) {}
			angle_( const angle_< angle_unit::degrees, T >& a ) : value( deg_to_rad( a.value ) ) {}
			static angle_< angle_unit::radians, T > make( const T& value ) { return angle_< angle_unit::radians, T >( value ); }
			T value;

		private:
			explicit angle_( const T& v ) : value( v ) {}
		};

		template < typename T > using radian_ = angle_< angle_unit::radians, T >;
		template < typename T > using degree_ = angle_< angle_unit::degrees, T >;
		using radian = radian_< real_t >;
		using radianf = radian_< float >;
		using radiand = radian_< double >;
		using degree = degree_< real_t >;
		using degreef = degree_< float >;
		using degreed = degree_< double >;

		template< typename T > angle_<angle_unit::radians, T> rad( T rad ) { return angle_<angle_unit::radians, T>::make( rad ); }
		template< typename T > angle_<angle_unit::degrees, T> deg( T deg ) { return angle_<angle_unit::degrees, T>::make( deg ); }

		/// scalar multiplication
		template< angle_unit U, typename T > angle_<U, T> operator*( const T& s, const angle_<U, T>& a )
		{ return angle_<U, T>::make( s * a.value ); }
		template< angle_unit U, typename T > angle_<U, T> operator*( const angle_<U, T>& a, const T& s )
		{ return angle_<U, T>::make( s * a.value ); }

		template< angle_unit U, typename T > angle_<U, T> operator+( const angle_<U, T>& a1, const angle_<U, T>& a2 )
		{ return angle_<U, T>::make( a1.value + a2.value ); }

		template< angle_unit U, typename T > angle_<U, T> operator-( const angle_<U, T>& a1, const angle_<U, T>& a2 )
		{ return angle_<U, T>::make( a1.value - a2.value ); }

		template< typename T > T rad_value( const angle_<angle_unit::radians, T>& a ) { return a.value; }
		template< typename T > T rad_value( const angle_<angle_unit::degrees, T>& a ) { return deg_to_rad( a.value ); }

		template< angle_unit U, typename T > T sin( const angle_<U, T>& a ) { return std::sin( rad_value( a ) ); }
		template< angle_unit U, typename T > T cos( const angle_<U, T>& a ) { return std::cos( rad_value( a ) ); }
		template< angle_unit U, typename T > T tan( const angle_<U, T>& a ) { return std::tan( rad_value( a ) ); }
		template< angle_unit U, typename T > T asin( const angle_<U, T>& a ) { return std::asin( rad_value( a ) ); }
		template< angle_unit U, typename T > T acos( const angle_<U, T>& a ) { return std::acos( rad_value( a ) ); }
		template< angle_unit U, typename T > T atan( const angle_<U, T>& a ) { return std::atan( rad_value( a ) ); }
	}
}
