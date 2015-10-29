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
	}
}
