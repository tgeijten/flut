#pragma once

#include "mat33_type.hpp"
#include "vec3_type.hpp"

namespace flut
{
	namespace math
	{
		template< typename T >
		mat33_<T> mat33_from_axes( const vec3_<T>& x, const vec3_<T>& y, const vec3_<T>& z )
		{ return mat33_<T>( x.x, y.x, z.x, x.y, y.y, z.y, x.z, y.z, z.z ); }
	}
}
