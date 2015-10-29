#pragma once

#include <limits>
#include "../types.hpp"

namespace flut
{
	namespace math
	{
		template< typename E > struct vec3_
		{
			vec3_() {}
			vec3_( E x, E y, E z ) : x( x ), y( y ), z( z ) {}
			E x, y, z;
		};

		/// template instantiations
		typedef vec3_< real_t > vec3;
		typedef vec3_< float > vec3f;
		typedef vec3_< double > vec3d;

		template< typename T > struct v3i { const static bool value = false; };

		template<> struct v3i< vec3f >
		{
			typedef decltype( vec3f::x ) elem_t;
			static const elem_t& x( const vec3f& v ) { return v.x; }
			static const elem_t& y( const vec3f& v ) { return v.y; }
			static const elem_t& z( const vec3f& v ) { return v.z; }
			static vec3 make( elem_t x, elem_t y, elem_t z ) { return vec3( x, y, z ); }
			const static bool value = true;
		};

		template<> struct v3i< vec3d >
		{
			typedef decltype( vec3d::x ) elem_t;
			static const elem_t& x( const vec3d& v ) { return v.x; }
			static const elem_t& y( const vec3d& v ) { return v.y; }
			static const elem_t& z( const vec3d& v ) { return v.z; }
			static vec3 make( elem_t x, elem_t y, elem_t z ) { return vec3( x, y, z ); }
			const static bool value = true;
		};
	}
}
