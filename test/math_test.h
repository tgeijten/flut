#pragma once

#include "scone/Vec3.h"
#include "scone/Quat.h"
#include "flut/math/vec3.hpp"
#include "flut/math/quat.hpp"
#include "flut/math/random.hpp"
// TODO not on UNIX #include <conio.h>
#include <random>
#include <algorithm>
#include "flut/system/log.hpp"
#include "flut/math/angle.hpp"
#include "flut/math/unit_value.hpp"
#include "flut/flags.hpp"

using std::cout;
using std::endl;
using scone::Radian;

namespace flut
{
namespace math
{
template< typename T >
void compare( const vec3_<T>& v1, const scone::Vec3& v2, T e = constants<T>::relaxed_epsilon() )
{
	bool eq = equals( v1.x, v2.x, e ) && equals( v1.y, v2.y, e ) && equals( v1.z, v2.z, e );
	auto diff = std::abs( v1.x - v2.x ) + std::abs( v1.y - v2.y ) + std::abs( v1.z - v2.z );
	if ( eq ) log::info( "OK! diff=", diff, "v1=", v1, "v2=", v2 );
	else log::error( "ERROR! diff=", diff, "v1=", v1, "v2=", v2 );
}

template< typename T >
void compare( const quat_<T>& q1, const scone::Quat& q2, T e = constants<T>::relaxed_epsilon() )
{
	bool eq = equals( q1.w, q2.W(), e ) && equals( q1.x, q2.X(), e ) && equals( q1.y, q2.Y(), e ) && equals( q1.z, q2.Z(), e );
	auto diff = std::abs( q1.w - q2.W() ) + std::abs( q1.x - q2.X() ) + std::abs( q1.y - q2.Y() ) + std::abs( q1.z - q2.Z() );
	if ( eq ) log::info( "OK! diff=", diff, "q1=", q1, "q2=", q2 );
	else log::error( "ERROR! diff=", diff, "q1=", q1, "q2=", q2 );
}

void math_test()
{
	for ( size_t x = 0; x < 2000; ++x )
		if ( is_power_of_two( x ) )
			log::debug( x, " is a power of 2" );

	enum TestEnum { Apple, Pear, Banana, Orange };
	flags< TestEnum > flg;
	flg.set( Apple, true );
	flg.set( Banana, true );
	flut_logvar4( flg.get( Apple ), flg.get( Pear ), flg.get( Banana ), flg.get( Orange ) );
	flg.set( Banana, false );
	flg.set( Orange, true );
	flut_logvar4( flg.get<Apple>(), flg.get( Pear ), flg.get( Banana ), flg.get( Orange ) );

	//auto ang1 = degree( 45 );
	//auto ang2 = radian( ang1 );
	//auto ang3 = ang1 + degree( 180 );

	auto a1 = rad( constants< float >::half_pi() );
	auto a2 = deg( 180.0f );
	auto a3 = a1 + radian_< float >( a2 );
	auto a4 = a2 + degree_< float >( a1 );

	auto a5 = 0.5 * a1;
	auto a6 = 0.5 * a2;

	auto sin1 = sin( a1 );
	auto sin4 = sin( a4 );
	
	//auto qtest = make_quat_from_euler( deg( 10.0 ), deg( 10.0 ), deg( 10.0 ), euler_order::xyz );
	auto qtest2 = make_quat_from_axis_angle( vec3_< float >::make_unit_x(), radian_< float >( 90 ) );

	//flut_logvar4( a1.value, a2.value, a3.value, a4.value );
	flut_logvar4( sizeof( a1 ), sizeof( a2 ), sizeof( a3 ), sizeof( a4 ) );

	std::default_random_engine re( 123 );
	std::uniform_real_distribution<> rd( -10, 10 );

	for ( size_t experiment = 0; experiment < 10; ++experiment )
	{
		std::vector< double > rv( 16 );
		std::generate( rv.begin(), rv.end(), [&]() { return rd( re ); } );

		auto flut_v1 = vec3( rv[0], rv[1], rv[2] );
		auto flut_v2 = vec3( rv[3], rv[4], rv[5] );
		auto flut_x = normalized( flut_v2 - flut_v1 );
		auto flut_y = normalized( cross_product( flut_x, normalized( flut_v2 ) ) );
		auto flut_z = cross_product( flut_x, flut_y );
		flut_logvar3( flut_x.length(), flut_y.length(), flut_z.length() );
		auto flut_q1 = make_quat_from_axes( flut_x, flut_y, flut_z );
		auto flut_q2 = make_quat_from_axis_angle( normalized( vec3( rv[6], rv[7], rv[8] ) ), rad( rv[9] ) );
		auto flut_q3 = flut_q1 * flut_q2;
		auto flut_q4 = normalized( flut_q3 );
		flut_logvar3( length(flut_q1), length(flut_q2), length(flut_q3) );
		auto flut_v4 = flut_q4 * flut_v1;
		auto flut_v5 = make_rotation_vector( flut_q4 );

		auto scone_v1 = scone::Vec3( rv[0], rv[1], rv[2] );
		auto scone_v2 = scone::Vec3( rv[3], rv[4], rv[5] );
		auto scone_x = ( scone_v2 - scone_v1 ).GetNormalized();
		auto scone_y = ( scone_x.GetCrossProduct( scone_v2.GetNormalized() ) ).GetNormalized();
		auto scone_z = scone_x.GetCrossProduct( scone_y );
		auto scone_q1 = QuatFromAxes( scone_x, scone_y, scone_z );
		auto scone_q2 = QuatFromAxisAngle( scone::Vec3( rv[6], rv[7], rv[8] ).GetNormalized(), scone::Radian( rv[9] ) );
		auto scone_q3 = scone_q1 * scone_q2;
		auto scone_q4 = scone_q3.GetNormalized();
		auto scone_v4 = scone_q4 * scone_v1;
		auto scone_v5 = scone_q4.ToExponentialMap2();

		compare( flut_v1, scone_v1 );
		compare( flut_v2, scone_v2 );
		compare( flut_x, scone_x );
		compare( flut_y, scone_y );
		compare( flut_z, scone_z );
		compare( flut_q1, scone_q1 );
		compare( flut_q2, scone_q2 );
		compare( flut_q3, scone_q3 );
		compare( flut_v4, scone_v4 );
		compare( flut_v5, scone_v5 );

		// euler angle test
		euler_order flut_eo[] = { euler_order::xyz, euler_order::xzy, euler_order::yxz, euler_order::yzx, euler_order::zxy, euler_order::zyx };
		scone::EulerOrder scone_eo[] = { scone::EULER_ORDER_XYZ, scone::EULER_ORDER_XZY, scone::EULER_ORDER_YXZ, scone::EULER_ORDER_YZX, scone::EULER_ORDER_ZXY, scone::EULER_ORDER_ZYX };

		for ( int j = 0; j < 6; ++j )
		{
			auto flut_qeo = make_quat_from_euler< real_t >( rad( rv[0] ), rad( rv[1] ), rad( rv[2] ), flut_eo[ j ] );
			auto scone_qeo = QuatFromEuler( Radian( rv[0] ), Radian( rv[1] ), Radian( rv[2] ), scone_eo[j] );
			compare( flut_qeo, scone_qeo );
		}
	}
}
}
}
