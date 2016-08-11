#pragma once

#include "flut/system/types.hpp"
#include "flut/prop_node.hpp"

namespace flut
{
	namespace math
	{
		template< typename T >
		struct quat_
		{
		public:
			quat_() {}
			quat_( const prop_node& pn ) : w( pn.get<T>( "w" ) ), x( pn.get<T>( "x" ) ), y( pn.get<T>( "y" ) ), z( pn.get<T>( "z" ) ) {}
			quat_( T w, T x, T y, T z ) : w( w ), x( x ), y( y ), z( z ) {}
			template< typename T2 > quat_( const quat_<T2>& o ) : w( T(o.w) ), x( T(o.x) ), y( T(o.y) ), z( T(o.z) ) {}
			template< typename T2 > quat_<T>& operator=( const quat_<T2>& o ) { w = T(o.w); x = T(o.x); y = T(o.y); z = T(o.z); return *this; }

			/// convert to prop_node
			explicit operator prop_node() const { return prop_node().set( "w", w ).set( "x", x ).set( "y", y ).set( "z", z ); }

			/// member access
			T w, x, y, z;

			/// generate quat with zero rotation
			static quat_<T> zero() { return quat_<T>( T(1), T(0), T(0), T(0) ); }
		};
		
		typedef quat_< real_t > quat;
		typedef quat_< float > quatf;
		typedef quat_< double > quatd;
	}

	template< typename T > struct prop_node_cast< math::quat_<T> > {
		static math::quat_<T> from( const prop_node& pn ) { return math::quat_<T>( pn ); }
		static prop_node to( const math::quat_<T>& q ) { return static_cast< prop_node >( q ); }
	};
}
