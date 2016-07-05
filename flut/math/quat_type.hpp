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
			T w, x, y, z;

			static quat_<T> make_zero() { return quat_<T>( T(0), T(0), T(0), T(1) ); }
		};
		
		typedef quat_< real_t > quat;
		typedef quat_< float > quatf;
		typedef quat_< double > quatd;
	}
}
