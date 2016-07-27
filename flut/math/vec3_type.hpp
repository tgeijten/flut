#pragma once

#include <cmath>
#include "flut/system/types.hpp"
#include "flut/prop_node.hpp"

namespace flut
{
	namespace math
	{
		template< typename T > struct vec3_
		{
			vec3_() {}
			vec3_( const prop_node& pn ) : x( pn.get<T>( "x" ) ), y( pn.get<T>( "y" ) ), z( pn.get<T>( "z" ) ) {}
			vec3_( T px, T py, T pz ) : x( px ), y( py ), z( pz ) {}
			template< typename T2 > vec3_( const vec3_<T2>& o ) : x( T(o.x) ), y( T(o.y) ), z( T(o.z) ) {}
			template< typename T2 > vec3_<T>& operator=( const vec3_<T2>& o ) { x = T(o.x); y = T(o.y); z = T(o.z); return *this; }

			/// convert to prop_node
			explicit operator prop_node() const { return prop_node().set( "x", x ).set( "y", y ).set( "z", z ); }

			/// element access
			const T& operator[]( index_t idx ) const { return (&x)[idx]; }
			T& operator[]( index_t idx ) { return (&x)[idx]; }
			T x, y, z;

			/// const properties
			T length() const { return sqrt( x * x + y * y + z * z ); }
			T squared_length() const { return x * x + y * y + z * z; }
			bool is_null() const { return x == T(0) && y == T(0) && z == T(0); }

			/// static initializers
			static vec3_<T> make_zero() { return vec3_<T>( T(0), T(0), T(0) ); }
			static vec3_<T> make_unit_x() { return vec3_<T>( T(1), T(0), T(0) ); }
			static vec3_<T> make_unit_y() { return vec3_<T>( T(0), T(1), T(0) ); }
			static vec3_<T> make_unit_z() { return vec3_<T>( T(0), T(0), T(1) ); }
		};

		/// template instantiations
		typedef vec3_< real_t > vec3;
		typedef vec3_< float > vec3f;
		typedef vec3_< double > vec3d;
	}

	template< typename T > struct prop_node_converter< math::vec3_<T> > {
		static math::vec3_<T> get( const prop_node& pn ) { return math::vec3_<T>( pn ); }
		static void set( prop_node& pn, const math::vec3_<T>& vec ) { pn = static_cast< prop_node >( vec ); }
	};
}
