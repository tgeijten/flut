#pragma once

#include "vec3_type.hpp"
#include <limits>

namespace flut
{
	namespace math
	{
		/// Addition
		template< typename T > vec3_<T> operator+( const vec3_<T>& v1, const vec3_<T>& v2 )
		{ return vec3_<T>( v1.x + v2.x, v1.y + v2.y, v1.z + v2.z ); }

		/// Subtraction
		template< typename T > vec3_<T> operator-( const vec3_<T>& v1, const vec3_<T>& v2 )
		{ return vec3_<T>( v1.x - v2.x, v1.y - v2.y, v1.z - v2.z ); }

		/// Scalar multiplication
		template< typename T > vec3_<T> operator*( T s, const vec3_<T>& v )
		{ return vec3_<T>( s * v.x, s * v.y, s * v.z ); }
		template< typename T > vec3_<T> operator*( const vec3_<T>& v, T s )
		{ return vec3_<T>( s * v.x, s * v.y, s * v.z ); }
		template< typename T > vec3_<T> operator*=( vec3_<T>& v, T s )
		{ v.x *= s; v.y *= s; v.z *= s; return v; }

		/// Get length of a vec3
		template< typename T > T length( vec3_<T> v )
		{ return sqrt( v.x * v.x + v.y * v.y + v.z * v.z ); }

		/// Get squared length of a vec3
		template< typename T > T squared_length( vec3_<T> v )
		{ return v.x * v.x + v.y * v.y + v.z * v.z; }

		/// Get normalized vec3
		template< typename T > vec3_<T> normalized( vec3_<T> v )
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
