#pragma once

#include "../types.hpp"

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
		};
		
		typedef quat_< real_t > quat;
		typedef quat_< float > quatf;
		typedef quat_< double > quatd;
		
		template< typename Q > struct v4i { const static bool value = false; };
		
		template<> struct v4i< quatf >
		{
			typedef float elem_t;
			static const elem_t& w( const quatf& q ) { return q.w; }
			static const elem_t& x( const quatf& q ) { return q.x; }
			static const elem_t& y( const quatf& q ) { return q.y; }
			static const elem_t& z( const quatf& q ) { return q.z; }
			static quatf make( elem_t w, elem_t x, elem_t y, elem_t z ) { return quatf( w, x, y, z ); }
			const static bool value = true;
		};
		
		template<> struct v4i< quatd >
		{
			typedef double elem_t;
			static const elem_t& w( const quatd& q ) { return q.w; }
			static const elem_t& x( const quatd& q ) { return q.x; }
			static const elem_t& y( const quatd& q ) { return q.y; }
			static const elem_t& z( const quatd& q ) { return q.z; }
			static quatd make( elem_t w, elem_t x, elem_t y, elem_t z ) { return quatd( w, x, y, z ); }
			const static bool value = true;
		};
	}
}

