#pragma once

#include "flut/system/types.hpp"

namespace flut
{
	namespace math
	{
		template< typename T >
		struct transform_
		{
			vec3_< T > pos;
			quat_< T > rot;

			vec3_< T > transformed( const vec3_< T >& v ) { return pos + rot * v; }
			vec3_< T > inv_transformed( const vec3_< T >& v ) { return -rot * ( v - pos ); }
		};

		typedef transform_< real_t > transform;
		typedef transform_< float > transformf;
		typedef transform_< double > transformd;
	}
}
