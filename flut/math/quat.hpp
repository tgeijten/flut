#pragma once

#include "quat_type.hpp"
#include "mat33.hpp"
#include "math_types.hpp"
#include "../system/assert.hpp"

namespace flut
{
	namespace math
	{
		/** Quaternion multiplication. */
		template< typename T > quat_<T> operator*( const quat_<T>& q1, const quat_<T>& q2 )
		{
			return quat_<T>(
				q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z,
				q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y,
				q1.w * q2.y + q1.y * q2.w + q1.z * q2.x - q1.x * q2.z,
				q1.w * q2.z + q1.z * q2.w + q1.x * q2.y - q1.y * q2.x );
		}

		/** Vector multiplication. */
		template< typename T > vec3_<T> operator*( const quat_<T>& q, const vec3_<T>& v )
		{
			vec3_<T> qv( q.x, q.y, q.z );
			vec3_<T> uv = cross_product( qv, v );
			vec3_<T> uuv = cross_product( qv, uv );
			uv *= T( 2 ) * q.w;
			uuv *= T( 2 );
			return v + uv + uuv;
		}

		/** Negation (conjugate). */
		template< typename T > quat_<T> operator-( const quat_<T>& q )
		{ return quat_<T>( q.w, -q.x, -q.y, -q.z ); }

		/** Normalize. */
		template< typename T > quat_<T>& normalize( quat_<T>& q )
		{
			T l = sqrt( q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w );
			if ( l > constants<T>::epsilon() )
			{ T invl = T( 1 ) / l; q.x *= invl; q.y *= invl; q.z *= invl; q.w *= invl; }
			return q;
		}

		/** Get quaternion using an axis and an angle. */
		template< typename T > quat_<T> make_quat_from_axis_angle( const vec3_<T>& axis, radian angle )
		{
			// axis must be of unit length! (this is not enforced)
			T ha = T( 0.5 ) * angle.value;
			T hs = sin( ha );
			return quat_<T>( cos( ha ), hs * axis.x, hs * axis.y, hs * axis.z );
		}

		/** Get quaternion using Euler angles. */
		template< typename T > quat_<T> make_quat_from_euler( radian x, radian y, radian z, euler_order eo = euler_order::xyz )
		{ FLUT_NOT_IMPLEMENTED; }

		/** Get quaternion to represent the rotation from source to target vector. */
		template< typename T > quat_<T> quat_from_directions( const vec3_<T>& source, const vec3_<T>& target )
		{ FLUT_NOT_IMPLEMENTED; }

		/** Get quaternion to represent the rotation from source to target quaternion. */
		template< typename T > quat_<T> quat_from_quats( const quat_<T>& source, const quat_<T>& target )
		{ FLUT_NOT_IMPLEMENTED; }

		/** Get quaternion from rotation vector. */
		template< typename T > quat_<T> quat_from_rotation_vector( const vec3_<T>& v )
		{ FLUT_NOT_IMPLEMENTED; }

		/** Get quaternion using three axis vectors. */
		template< typename T > quat_<T> make_quat_from_axes( const vec3_<T>& x, const vec3_<T>& y, const vec3_<T>& z )
		{
			quat_<T> q;
			mat33_<T> m = mat33_from_axes( x, y, z );

			T t = m[0][0] + m[1][1] + m[2][2];
			if ( t > 0.0 )
			{
				T root = sqrt( t + T( 1 ) );
				q.w = 0.5f * root;
				root = 0.5f / root;
				q.x = ( m[2][1] - m[1][2] ) * root;
				q.y = ( m[0][2] - m[2][0] ) * root;
				q.z = ( m[1][0] - m[0][1] ) * root;
			}
			else
			{
				size_t i = 0;
				if ( m[1][1] > m[0][0] ) i = 1;
				if ( m[2][2] > m[i][i] ) i = 2;
				size_t j = i % 3;
				size_t k = j % 3;

				T root = sqrt( m[i][i] - m[j][j] - m[k][k] + T( 1 ) );
				T* q_ptrs[3] = { &q.x, &q.y, &q.z };
				*q_ptrs[i] = T( 0.5 ) * root;
				root = T( 0.5 ) / root;
				q.w = ( m[k][j] - m[j][k] ) * root;
				*q_ptrs[j] = ( m[j][i] + m[i][j] ) * root;
				*q_ptrs[k] = ( m[k][i] + m[i][k] ) * root;
			}

			return q;
		}
	}
}
