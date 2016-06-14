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

		template< angle_unit A, angle_unit B > struct angle_converter
		{ template< typename T > static const T& convert( const T& v ) { return v; } };

		template<> struct angle_converter< angle_unit::degrees, angle_unit::radians >
		{ template< typename T > static T convert( T v ) { return deg_to_rad( v ); } };

		template<> struct angle_converter< angle_unit::radians, angle_unit::degrees >
		{ template< typename T > static T convert( T v ) { return rad_to_deg( v ); } };

		template< angle_unit U, typename T >
		struct angle_
		{
			/// default constructor
			explicit angle_() : value( T(0) ) {}

			/// explicit constructor
			explicit angle_( const T& v ) : value( v ) {}

			/// copy constructor
			explicit angle_( const angle_<U, T>& a ) : value( a.value ) {}

			/// constructor that takes angle, converts unit and value type
			template< angle_unit U2, typename T2 > angle_( const angle_<U2, T2>& a ) : value( angle_converter<U2, U>::convert( T( a.value ) ) ) {}

			/// assignment that takes angle, converts unit and value type
			template< angle_unit U2, typename T2 > angle_<U, T>& operator=( const angle_<U2, T2>& a ) { value = angle_converter<U2, U>::convert( T( a.value ) ); return *this; }

			/// return degree copy
			angle_< angle_unit::degrees, T > degree() const { return angle_< angle_unit::degrees, T >( angle_converter< U, angle_unit::degrees >::convert( value ) ); }
			angle_< angle_unit::radians, T > radian() const { return angle_< angle_unit::radians, T >( angle_converter< U, angle_unit::radians >::convert( value ) ); }

			/// get rad / deg value
			T deg_value() const { return angle_converter< U, angle_unit::degrees >::convert( value ); }
			T rad_value() const { return angle_converter< U, angle_unit::radians >::convert( value ); }

			/// scalar multiplication and division
			template< typename TS > angle_& operator*=( const TS& s ) { value *= T(s); return *this; }
			template< typename TS > angle_ operator*( const TS& s ) const { return angle_( value * T(s) ); }
			template< typename TS > angle_& operator/=( const TS& s ) { value /= T(s); return *this; }
			template< typename TS > angle_ operator/( const TS& s ) const { return angle_( value / T(s) ); }

			/// addition / subtraction of an angle with the same units
			angle_& operator+=( const angle_& other ) { value += other.value; return *this; }
			angle_& operator-=( const angle_& other ) { value -= other.value; return *this; }

			/// negation
			angle_ operator-() const { return angle_( -value ); }

			/// comparison operators
			bool operator>( const angle_& other ) const { return value > other.value; }
			bool operator<( const angle_& other ) const { return value < other.value; }
			bool operator>=( const angle_& other ) const { return value >= other.value; }
			bool operator<=( const angle_& other ) const { return value <= other.value; }
			bool operator==( const angle_& other ) const { return value == other.value; }
			bool operator!=( const angle_& other ) const { return value != other.value; }

			/// actual value
			T value;
		};

		// alias names
		template < typename T > using radian_ = angle_< angle_unit::radians, T >;
		template < typename T > using degree_ = angle_< angle_unit::degrees, T >;
		using radian = radian_< real_t >;
		using radianf = radian_< float >;
		using radiand = radian_< double >;
		using degree = degree_< real_t >;
		using degreef = degree_< float >;
		using degreed = degree_< double >;

		template< typename T > angle_< angle_unit::radians, T > make_rad( T rad ) { return angle_<angle_unit::radians, T>( rad ); }
		template< typename T > angle_< angle_unit::degrees, T > make_deg( T deg ) { return angle_<angle_unit::degrees, T>( deg ); }

		/// scalar multiplication
		template< angle_unit U, typename T, typename TS >
		angle_<U, T> operator*( const TS& s, const angle_<U, T>& a ) { return angle_<U, T>( T(s) * a.value ); }

		/// scalar division
		template< angle_unit U, typename T, typename TS >
		angle_<U, T> operator/( const TS& s, const angle_<U, T>& a ) { return angle_<U, T>( T(s) / a.value ); }

		/// addition, value types can be different
		template< angle_unit U, typename T1, typename T2 >
		auto operator+( const angle_<U, T1>& a1, const angle_<U, T2>& a2 ) -> angle_<U, decltype( a1.value + a2.value )>
		{ return angle_<U, decltype( a1.value + a2.value )>( a1.value + a2.value ); }

		/// subtraction, value types can be different
		template< angle_unit U, typename T1, typename T2 >
		auto operator-( const angle_<U, T1>& a1, const angle_<U, T2>& a2 ) -> angle_<U, decltype( a1.value - a2.value )>
		{ return angle_<U, decltype( a1.value - a2.value )>( a1.value - a2.value ); }

		/// sin/cos/tan
		template< typename T > T sin( const radian_<T>& a ) { return std::sin( a.value ); }
		template< typename T > T cos( const radian_<T>& a ) { return std::cos( a.value ); }
		template< typename T > T tan( const radian_<T>& a ) { return std::tan( a.value ); }
		template< typename T > T asin( const radian_<T>& a ) { return std::asin( a.value ); }
		template< typename T > T acos( const radian_<T>& a ) { return std::acos( a.value ); }
		template< typename T > T atan( const radian_<T>& a ) { return std::atan( a.value ); }

		/// streaming
		template< angle_unit U, typename T > std::ostream& operator<<( std::ostream& str, const angle_<U, T>& a )
		{ return ( str << a.value ); }

		template< angle_unit U, typename T > std::istream& operator>>( std::istream& str, angle_<U, T>& a )
		{ return ( str >> a.value ); }
	}
}
