#pragma once

#include "flut/system/types.hpp"

namespace flut
{
	namespace math
	{
		template< typename T >
		struct quat_
		{
		public:
			quat_() {}
			quat_( T w, T x, T y, T z ) : w( w ), x( x ), y( y ), z( z ) {}
			template< typename T2 > quat_( const quat_<T2>& o ) : w( T(o.w) ), x( T(o.x) ), y( T(o.y) ), z( T(o.z) ) {}
			template< typename T2 > quat_<T>& operator=( const quat_<T2>& o ) { w = T(o.w); x = T(o.x); y = T(o.y); z = T(o.z); return *this; }

			T w, x, y, z;

			static quat_<T> make_zero() { return quat_<T>( T(0), T(0), T(0), T(1) ); }
		};
		
		typedef quat_< real_t > quat;
		typedef quat_< float > quatf;
		typedef quat_< double > quatd;
	}
}
