#pragma once

#include "vec3_tmp.hpp"
#include "quat_type.hpp"

namespace flut
{
	namespace math
	{
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

		/** Get quaternion using three axis vectors. */
		template< typename Q, typename V > Q make_from_axes( const V& x, const V& y, const V& z )
		{
			return v4i<Q>::make( 1, 0, 0, 0 );
		}

		template< typename Q1, typename Q2 > Q1 make_from_quat( const Q2& q )
		{ return v4i<Q1>::make( v4i<Q2>::w( q ), v4i<Q2>::x( q ), v4i<Q2>::y( q ), v4i<Q2>::z( q ) ); }


		/** Quaternion multiplication. */
		template< typename T > quat_<T> operator*( const quat_<T>& q1, const quat_<T>& q2 );

		/** Vector multiplication. */
		template< typename Q, typename V > V operator*( const Q& q, const V& v )
		{
			V qv = v3i<V>::make( v4i<Q>::x(q), v4i<Q>::y(q), v4i<Q>::z(q) );
			V uv = cross_product( qv, v );
			V uuv = cross_product( qv, uv );
			uv *= v3i<V>::elem_t( 2 ) * v4i<Q>::w( q );
			uuv *= v3i<V>::elem_t( 2 );
			return v + uv + uuv;
		}

		/** Negation (conjugate). */
		template< typename T > quat_<T> operator-( const quat_<T>& q );

		/** Normalize. */
		template< typename T > quat_<T>& normalize( const quat_<T>& q );

		/** Get Normalized. */
		template< typename T > quat_<T> normalized( const quat_<T>& q );

		/** Get quaternion using an axis and an angle. */
		//template< typename T > quat_<T> quat_from_axes( const vec3_<T>& axis, const Radian& angle );

		/** Get quaternion using Euler angles. */
		//template< typename T > quat<T> quat_from_euler( const Radian& xAngle, const Radian& yAngle, const Radian& zAngle, EulerOrder eulerOrder = EULER_ORDER_XYZ );

		/** Get quaternion to represent the rotation from source to target vector. */
		template< typename T > quat_<T> make_quat_from_directions( const vec3_<T>& source, const vec3_<T>& target );

		/** Get quaternion to represent the rotation from source to target quaternion. */
		template< typename T > quat_<T> quat_from_quats( const quat_<T>& source, const quat_<T>& target );

		/** Get quaternion from rotation vector. */
		template< typename T > quat_<T> quat_from_rotation_vector( const vec3_<T>& v );
	}
}
