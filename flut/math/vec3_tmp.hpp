#pragma once

#include <limits>

#include "vec3_type.hpp"

namespace flut
{
	namespace math
	{
		/// Addition
		template< typename T > T operator+( const T& v1, const T& v2 )
		{ return v3i<T>::make( v3i<T>::x(v1) + v3i<T>::x(v2), v3i<T>::y(v1) + v3i<T>::y(v2), v3i<T>::z(v1) + v3i<T>::z(v2) ); }

		/// Subtraction
		template< typename T > T operator-( const T& v1, const T& v2 )
		{ return v3i<T>::make( v3i<T>::x(v1) - v3i<T>::x(v2), v3i<T>::y(v1) - v3i<T>::y(v2), v3i<T>::z(v1) - v3i<T>::z(v2) ); }

		/// Scalar multiplication
		template< typename T > vec3_<T> operator*( T s, const vec3_<T>& v )
		{ return vec3_<T>( s * v.x, s * v.y, s * v.z ); }
		template< typename T > vec3_<T> operator*( const vec3_<T>& v, T s )
		{ return vec3_<T>( s * v.x, s * v.y, s * v.z ); }
		template< typename T > vec3_<T> operator*=( vec3_<T>& v, T s )
		{ v.x *= s; v.y *= s; v.z *= s; return v; }

		/// Get length of a vec3
		template< typename T > T length( const vec3_<T>& v )
		{ return sqrt( v.x * v.x + v.y * v.y + v.z * v.z ); }

		/// Get squared length of a vec3
		template< typename T > T squared_length( const vec3_<T>& v )
		{ return v.x * v.x + v.y * v.y + v.z * v.z; }

		/// Get normalized vec3
		template< typename T > vec3_<T> normalized( const vec3_<T>& v )
		{
			T l = length( v );
			if ( l > std::numeric_limits< T >::epsilon() ) return ( T( 1 ) / l ) * v;
			else return vec3_<T>( 0 );
		}

		/// Normalize a vec3
		template< typename T > void normalize( vec3_<T>& v )
		{
			T l = length( v );
			if ( l > std::numeric_limits< T >::epsilon() )
			{ T inv_l = T( 1 ) / l; v.x *= s; v.y *= s; v.z *= s; }
		}

		/// Dot product of two vec3
		template< typename T > T dot_product( const vec3_<T>& v1, const vec3_<T>& v2 )
		{ return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; }

		/// Cross product
		template< typename T > vec3_<T> cross_product( const vec3_<T>& v1, const vec3_<T>& v2 )
		{ return vec3_<T>( v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x ); }

		/// stream out
		template< typename T >
		std::ostream& operator<<( std::ostream& str, const vec3_<T>& v )
		{ str << v.x << ' ' << v.y << ' ' << v.z; return str; }

		/// stream in
		template< typename T >
		std::istream& operator>>( std::istream& str, vec3_<T>& v )
		{ str >> v.x >> v.y >> v.z; return str; }
	}
}
