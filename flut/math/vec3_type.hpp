#pragma once

#include <limits>
#include "../types.hpp"

namespace flut
{
	namespace math
	{
		template< typename T > struct vec3_
		{
			vec3_() {}
			vec3_( T px, T py, T pz ) : x( px ), y( py ), z( pz ) {}

			// element access
			const T& operator[]( index_t idx ) const { return (&x)[idx]; }
			T& operator[]( index_t idx ) { return (&x)[idx]; }
			T x, y, z;

			// const properties
			T length() const { return sqrt( x * x + y * y + z * z ); }
			T squared_length() const { return x * x + y * y + z * z; }
			bool is_null() { return x == T(0) && y == T(0) && z == T(0); }

			// static initializers
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
}
