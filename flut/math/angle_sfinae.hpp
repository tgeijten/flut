#pragma once

#include <cmath>
#include "math.hpp"
#include "result_type.hpp"
#include "flut/system/assert.hpp"

namespace flut
{
	namespace math
	{
		// degree and radian structs;
		template< typename T > struct degree_;
		template< typename T > struct radian_;

		template< typename T >
		struct degree_
		{
			typedef T value_t;
			degree_( const radian_< T >& v ) : value( rad_to_deg( v.value ) ) {}
			explicit degree_( const T& v ) : value( v ) {}
			T value;
		};

		template< typename T >
		struct radian_
		{
			typedef T value_t;
			radian_( const degree_<T>& v ) : value( deg_to_rad( v.value ) ) {}
			explicit radian_( const T& v ) : value( v ) {}
			T value;
		};

		// SFINAE class
		template< typename C > struct is_angle_type { const static bool value = false; };
		template<> struct is_angle_type< radian_< float > > { const static bool value = true; };
		template<> struct is_angle_type< radian_< double > > { const static bool value = true; };
		template<> struct is_angle_type< degree_< float > > { const static bool value = true; };
		template<> struct is_angle_type< degree_< double > > { const static bool value = true; };

		// easy construction
		template< typename T > radian_<T> rad( T rad ) { return radian_<T>( rad ); }
		template< typename T > degree_<T> deg( T deg ) { return degree_<T>( deg ); }

		/// scalar multiplication
		template< typename T > typename std::enable_if< is_angle_type< T >::value, T >::type
		operator*( typename const T::value_t& s, const T& a ) { return T( s * a.value ); }

		// addition
		// TODO: make it work with different types of value_t?
		template< typename T > typename std::enable_if< is_angle_type< T >::value, T >::type
		operator+( const T& a1, const T& a2 ) { return T( a1.value + a2.value ); }

		//template< typename T > radian_<T> operator+( const radian_<T>& a1, const radian_<T>& a2 )
		//{ return radian_<T>( a1.value + a2.value ); }
		//template< typename T > degree_<T> operator+( const degree_<T>& a1, const degree_<T>& a2 )
		//{ return degree_<T>( a1.value + a2.value ); }

		//template< angle_unit U, typename T > angle_<U, T> operator*( const angle_<U, T>& a, const T& s )
		//{ return angle_<U, T>::make( s * a.value ); }

		//template< angle_unit U, typename T > angle_<U, T> operator-( const angle_<U, T>& a1, const angle_<U, T>& a2 )
		//{ return angle_<U, T>::make( a1.value - a2.value ); }

		template< typename T > T rad_value( const radian_<T>& a ) { return a.value; }
		template< typename T > T rad_value( const degree_<T>& a ) { return deg_to_rad( a.value ); }

		template< typename T > typename T::value_t sin( const T& a ) { return std::sin( rad_value( a ) ); }
		template< typename T > typename T::value_t cos( const T& a ) { return std::cos( rad_value( a ) ); }
		template< typename T > typename T::value_t tan( const T& a ) { return std::tan( rad_value( a ) ); }
		//template< angle_unit U, typename T > T asin( const angle_<U, T>& a ) { return std::asin( rad_value( a ) ); }
		//template< angle_unit U, typename T > T acos( const angle_<U, T>& a ) { return std::acos( rad_value( a ) ); }
		//template< angle_unit U, typename T > T atan( const angle_<U, T>& a ) { return std::atan( rad_value( a ) ); }
	}
}
