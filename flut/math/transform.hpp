#pragma once

#include "flut/system/types.hpp"
#include "flut/math/vec3.hpp"
#include "flut/math/quat.hpp"

namespace flut
{
	namespace math
	{
		template< typename T >
		struct transform_
		{
			transform_() {}
			transform_( vec3_<T> pos, quat_<T> ori ) : p( pos ), q( ori ) {}
			transform_( vec3_<T> pos ) : p( pos ), q( quat_<T>::zero() ) {}
			transform_( quat_<T> ori ) : p( vec3_<T>::make_zero() ), q( ori ) {}
			vec3_<T> p;
			quat_<T> q;

			void transform( vec3_<T>& pos ) const { pos = p + q * pos; }
			void transform( quat_<T>& ori ) const { ori = q * ori; }
			void transform( transform_<T>& t ) const { pos = p + q * pos; ori = q * ori; }
			vec3_<T> transformed( const vec3_<T>& v ) const { return p + q * v; }
			vec3_<T> inv_transformed( const vec3_<T>& v ) const { return -q * ( v - p ); }

			static transform_<T> zero() { return transform_<T>( vec3_<T>::make_zero(), quat_<T>::zero() ); }
		};

		typedef transform_< real_t > transform;
		typedef transform_< float > transformf;
		typedef transform_< double > transformd;
	}
}
