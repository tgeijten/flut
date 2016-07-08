#pragma once

#include "math.hpp"
#include "quat_type.hpp"
#include "mat33.hpp"
#include "flut/system/assert.hpp"
#include "flut/math/angle.hpp"
#include <ostream>

namespace flut
{
	namespace math
	{
		/// euler order for euler angle conversions
		enum class euler_order { xyz, xzy, yxz, yzx, zxy, zyx };

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
		template< typename T > quat_<T> operator-( quat_<T> q )
		{ q.x = -q.x; q.y = -q.y; q.z = -q.z; return q; }

		/// get length of a quat
		template< typename T > T length( quat_<T> v )
		{ return sqrt( v.w * v.w + v.x * v.x + v.y * v.y + v.z * v.z ); }

		/// test if a quat is of unit length
		template< typename T > bool is_normalized( quat_<T> v )
		{ return equals( v.w * v.w + v.x * v.x + v.y * v.y + v.z * v.z, T(1) ); }

		/** Normalize. */
		template< typename T > quat_<T>& normalize( quat_<T>& q )
		{
			T l = sqrt( q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w );
			if ( l > constants<T>::epsilon() )
			{ T invl = inv( l ); q.x *= invl; q.y *= invl; q.z *= invl; q.w *= invl; }
			return q;
		}

		/// get normalized quat
		template< typename T > quat_<T> normalized( quat_<T> q )
		{
			T l = sqrt( q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w );
			if ( l > constants<T>::epsilon() )
			{ T invl = inv( l ); q.w *= invl; q.x *= invl; q.y *= invl; q.z *= invl; }
			return q;
		}

		/// make quaternion from axis and angle
		template< typename T > quat_<T> make_quat_from_axis_angle( const vec3_<T>& axis, const radian_<T>& ang )
		{
			flut_assert( is_normalized( axis ) );
			auto ha = T( 0.5 ) * ang;
			T hs = sin( ha );
			return quat_<T>( cos( ha ), hs * axis.x, hs * axis.y, hs * axis.z );
		}

		/// make quaternion from Euler angles
		template< typename T > quat_<T> make_quat_from_euler( const radian_<T>& x, const radian_<T>& y, const radian_<T>& z, euler_order eo = euler_order::xyz )
		{
			T hxa = T( 0.5 ) * x.value, hya = T( 0.5 ) * y.value, hza = T( 0.5 ) * z.value;
			quat_<T> qx = quat_<T>( std::cos( hxa ), std::sin( hxa ), T( 0 ), T( 0 ) );
			quat_<T> qy = quat_<T>( std::cos( hya ), T( 0 ), std::sin( hya ), T( 0 ) );
			quat_<T> qz = quat_<T>( std::cos( hza ), T( 0 ), T( 0 ), std::sin( hza ) );
			switch ( eo )
			{
			case flut::math::euler_order::xyz: return qx * ( qy * qz );
			case flut::math::euler_order::xzy: return qx * ( qz * qy );
			case flut::math::euler_order::yxz: return qy * ( qx * qz );
			case flut::math::euler_order::yzx: return qy * ( qz * qx );
			case flut::math::euler_order::zxy: return qz * ( qx * qy );
			case flut::math::euler_order::zyx: return qz * ( qy * qx );
			default: flut_throw( "Unsupported euler_order" );
			}
		}

		/** Get quaternion to represent the rotation from source to target vector. */
		template< typename T > quat_<T> make_quat_from_directions( const vec3_<T>& source, const vec3_<T>& target )
		{
			vec3_<T> s = normalized( source );
			vec3_<T> t = normalized( target );
			vec3_<T> c = cross_product( s, t );
			T d = dot_product( s, t );

			if ( equals( d, T(1) ) ) // check if vectors are the same
				return quat_<T>::make_zero();

			auto clen = length( c );
			if ( equals( clen, T(0) ) ) // check if vectors are 180 deg apart
				return quat_<T>( 0, 1, 0, 0 ); // this doesn't work if source is unit_x

			c /= clen;
			auto a = std::acos( d ) * T(0.5);
			auto sa = std::sin( a );

			return quat_<T>( std::cos( a ), c.x * sa, c.y * sa, c.z * sa );
		}

		/** Get quaternion to represent the rotation from source to target quaternion. */
		template< typename T > quat_<T> quat_from_quats( const quat_<T>& source, const quat_<T>& target )
		{ FLUT_NOT_IMPLEMENTED; }

		/** Get quaternion from rotation vector. */
		template< typename T > vec3_<T> make_rotation_vector( const quat_<T>& q )
		{
			flut_assert( is_normalized( q ) );
			T len = sqrt( q.x * q.x + q.y * q.y + q.z * q.z );
			if ( len > constants<T>::epsilon() )
			{
				T f = T(2) * std::acos( q.w ) / len;
				return vec3_<T>( f * q.x, f * q.y, f * q.z );
			}
			else return vec3_<T>::make_zero();
		}

		/** Get quaternion using three axis vectors. */
		template< typename T > quat_<T> make_quat_from_axes( const vec3_<T>& x, const vec3_<T>& y, const vec3_<T>& z )
		{
			flut_assert( is_normalized( x ) && is_normalized( y ) && is_normalized( z ) );
			quat_<T> q;
			mat33_<T> m = mat33_from_axes( x, y, z );

			T t = m.e00 + m.e11 + m.e22;
			if ( t > 0.0 )
			{
				T root = sqrt( t + T( 1 ) );
				q.w = T( 0.5 ) * root;
				root = T( 0.5 ) / root;
				q.x = ( m.e21 - m.e12 ) * root;
				q.y = ( m[0][2] - m[2][0] ) * root;
				q.z = ( m[1][0] - m[0][1] ) * root;
			}
			else
			{
				size_t i = 0;
				if ( m[1][1] > m[0][0] ) i = 1;
				if ( m[2][2] > m[i][i] ) i = 2;
				size_t j = ( i + 1 ) % 3;
				size_t k = ( j + 1 ) % 3;
				T root = sqrt( m[i][i] - m[j][j] - m[k][k] + T( 1 ) );
				T* q_xyz = &q.x;
				q_xyz[i] = T( 0.5 ) * root;
				root = T( 0.5 ) / root;
				q.w = ( m[k][j] - m[j][k] ) * root;
				q_xyz[j] = ( m[j][i] + m[i][j] ) * root;
				q_xyz[k] = ( m[k][i] + m[i][k] ) * root;
			}

			return q;
		}

		/// Stream output
		template< typename T > std::ostream& operator<<( std::ostream& str, const quat_<T>& v )
		{ str << v.w << ' ' << v.x << ' ' << v.y << ' ' << v.z; return str; }
	}
}
