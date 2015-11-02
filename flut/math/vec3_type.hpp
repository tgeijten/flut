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
			vec3_( E px, E py, E pz ) : x( px ), y( py ), z( pz ) {}

			const E& operator[]( index_t idx ) const { return (&x)[idx]; }
			E& operator[]( index_t idx ) { return (&x)[idx]; }
			E x, y, z;
		};

		/// template instantiations
		typedef vec3_< real_t > vec3;
		typedef vec3_< float > vec3f;
		typedef vec3_< double > vec3d;
	}
}
