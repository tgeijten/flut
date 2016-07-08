#pragma once

#include <cmath>
#include "math.hpp"
#include "result_type.hpp"
#include "flut/system/assert.hpp"

namespace flut
{
	namespace math
	{
		template< typename UT, typename VT >
		struct angle_
		{
			VT value;
			angle_( VT v ) : value( v ) {}

			template< typename UT2, typename VT2 > UT operator+( const angle_<UT2, VT2>& other ) { return UT( value + VT( other.value ) ); }
			template< typename T > UT operator-( const angle_<UT, T>& other ) { return UT( value - other.value ); }
			template< typename T > friend UT operator*( T s, const angle_<UT, VT>& a ) { return UT( VT(s) * a.value ); }
		};

		template< typename T > struct radian_;
		template< typename T > struct degree_;

		template< typename T >
		struct degree_ : public angle_< degree_< T >, T >
		{
			explicit degree_( T v ) : angle_( v ) {}
			radian_<T> radian();
		};

		template< typename T >
		struct radian_ : public angle_< radian_< T >, T >
		{
			explicit radian_( T v ) : angle_( v ) {}
			radian_( degree_<T> deg );
			template< typename T2 > radian_( degree_<T2> deg );
			degree_<T> degree();
		};

		template< typename T > radian_<T>::radian_( degree_<T> deg ) : angle_( deg_to_rad( deg.value ) ) {}
		template< typename T > template< typename T2 > radian_<T>::radian_( degree_<T2> deg ) : angle_( deg_to_rad( T( deg.value ) ) ) {}

		template< typename T > radian_<T> degree_<T>::radian() { return radian_<T>( deg_to_rad( value ) ); }
		template< typename T > degree_<T> radian_< T >::degree() { return degree_<T>( rad_to_deg( value ) ); }

		// easy construction
		template< typename T > radian_<T> make_rad( const T& rad ) { return radian_<T>( rad ); }
		template< typename T > degree_<T> make_deg( const T& deg ) { return degree_<T>( deg ); }

		/// scalar multiplication
		//template< typename UT, typename VT > UT
		//operator*( VT s, const angle_<UT, VT>& a ) { return UT( s * a.value ); }

		// addition
		//template< typename UT, typename VT > UT operator+( const angle_<UT, VT>& a1, const angle_<UT, VT>& a2 )
		//{ return UT( a1.value + a2.value ); }

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

		template< typename T > T sin( const radian_<T>& a ) { return std::sin( a.value ); }
		template< typename T > T cos( const radian_<T>& a ) { return std::cos( a.value ); }
		template< typename T > T tan( const radian_<T>& a ) { return std::tan( a.value ); }
		//template< angle_unit U, typename T > T asin( const angle_<U, T>& a ) { return std::asin( rad_value( a ) ); }
		//template< angle_unit U, typename T > T acos( const angle_<U, T>& a ) { return std::acos( rad_value( a ) ); }
		//template< angle_unit U, typename T > T atan( const angle_<U, T>& a ) { return std::atan( rad_value( a ) ); }
	}
}
