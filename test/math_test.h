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
#include "flut/storage.hpp"
#include "flut/math/angle.hpp"
#include "flut/math/unit_value.hpp"
#include "flut/flag_set.hpp"
#include "flut/math/regular_piecewise_linear_function.hpp"
#include <fstream>
#include "flut/timer.hpp"
#include "flut/system_tools.hpp"
#include "flut/system/test_framework.hpp"
#include "flut/math/bounding_box.hpp"
#include "flut/math/math.hpp"
#include "flut/math/linear_regression.hpp"
#include "flut/math/irange.hpp"
#include "flut/math/optional.hpp"

using std::cout;
using std::endl;
using scone::Radian;

namespace flut
{
namespace math
{
template< typename T >
void compare( const vec3_<T>& v1, const scone::Vec3& v2, T e = num_const<T>::relaxed_epsilon() )
{
	bool eq = equals( v1.x, v2.x, e ) && equals( v1.y, v2.y, e ) && equals( v1.z, v2.z, e );
	auto diff = std::abs( v1.x - v2.x ) + std::abs( v1.y - v2.y ) + std::abs( v1.z - v2.z );
	FLUT_TEST_MSG( eq, stringf( "diff=%.6f", diff ) );
	//if ( eq ) log::info( "OK! diff=", diff, "v1=", v1, "v2=", v2 );
	//else log::error( "ERROR! diff=", diff, "v1=", v1, "v2=", v2 );
}

template< typename T >
void compare( const quat_<T>& q1, const scone::Quat& q2, T e = num_const<T>::relaxed_epsilon() )
{
	bool eq = equals( q1.w, q2.W(), e ) && equals( q1.x, q2.X(), e ) && equals( q1.y, q2.Y(), e ) && equals( q1.z, q2.Z(), e );
	auto diff = std::abs( q1.w - q2.W() ) + std::abs( q1.x - q2.X() ) + std::abs( q1.y - q2.Y() ) + std::abs( q1.z - q2.Z() );
	FLUT_TEST_MSG( eq, stringf( "diff=%.6f", diff ) );
	//if ( eq ) log::info( "OK! diff=", diff, "q1=", q1, "q2=", q2 );
	//else log::error( "ERROR! diff=", diff, "q1=", q1, "q2=", q2 );
}

double sin_func( double x ) { return std::sin( x ); }

void math_test()
{
	bounding_boxf bb;
	bb += vec3f( -1, 2, -3 );
	bb += vec3f( 3, -2, 1 );
	FLUT_TEST( bb.lower_bounds == vec3f( -1, -2, -3 ) );
	FLUT_TEST( bb.upper_bounds == vec3f( 3, 2, 1 ) );
}

void optional_test()
{
	optional< char > a;
	FLUT_TEST( sizeof( a ) == sizeof( char ) );
	FLUT_TEST( !a );
	a = 123;
	FLUT_TEST( a );
	FLUT_TEST( *a == 123 );
	a = -128;
	FLUT_TEST( !a );

	optional< double > b;
	FLUT_TEST( sizeof( b ) == sizeof( double ) );
	FLUT_TEST( !b );
	b = 1.234;
	FLUT_TEST( b );
	FLUT_TEST( *b == 1.234 );
	b = std::numeric_limits< double >::quiet_NaN();
	FLUT_TEST( !b );

	optional< vec3f > c;
	FLUT_TEST( sizeof( c ) != sizeof( vec3f ) );
	FLUT_TEST( !c );
	c = vec3f( 1, 2, 3 );
	FLUT_TEST( c );
	FLUT_TEST( *c == vec3f( 1, 2, 3 ) );
	optional< vec3d > d( vec3f( 3, 4, 5 ) );
	FLUT_TEST( d );
}

void function_test()
{
	regular_piecewise_linear_function< real_t > func( -real_pi, real_pi, 128, sin_func );

	std::ofstream ostr( "test.txt" );
	for ( real_t x = -2 * real_pi; x < 2 * real_pi; x += 0.1 )
		ostr << x << "\t" << func( x ) << endl;

	timer t;
	real_t result = 0.0, verify_result = 0.0;
	for ( int i = 0; i < 10000; ++i )
	{
		for ( real_t x = -real_pi; x <= real_pi; x += 0.001 )
		{
			result += func( x );
			verify_result += sin_func( x );
		}
	}
	auto duration = t.seconds();
	FLUT_TEST_MSG( equals( result, verify_result, 0.01 ), stringf( "diff=%f duration=%f", result - verify_result, duration ) );
}

void angle_test()
{
	//auto ang1 = degree( 45 );
	//auto ang2 = radian( ang1 );
	//auto ang3 = ang1 + degree( 180 );

	auto a1_rd = rad( num_const< double >::half_pi() );
	auto a2_dd = deg( 180.0 );
	auto a3 = a1_rd + a2_dd.radian();
	auto a4 = a2_dd + a1_rd.degree();

	auto a5_rf = radianf( deg( 90.0f ) );
	auto a6_df = degreef( radiand( num_const<float>::half_pi() ) );

	auto a1s = 0.5 * a1_rd;
	auto a2s = 0.5f * a2_dd;
	auto a3s = 2 * a3;

	auto sin1 = sin( a1_rd );
	auto sin4 = sin( a4 );

	vec3_< degreef > deg_vec( degreef( 10 ), degreef( 20 ), degreef( 30 ) );
	vec3_< radianf > rad_vec;
	rad_vec = deg_vec;
	FLUT_TEST( equals( rad_vec[ 0 ].value, radianf( degreef( 10 ) ).value ) );


	auto qtest = quat_from_euler( degree( 180.0 ), degree( 180 ), degree( 180 ).radian().degree(), euler_order::xyz );
	auto qtest2 = quat_from_axis_angle( vec3_<float>::unit_x(), a6_df );

	//flut_logvar4( a1.value, a2.value, a3.value, a4.value );
	flut_logvar4( sizeof( a1_rd ), sizeof( a2_dd ), sizeof( a3 ), sizeof( a4 ) );
}

void clamp_test()
{
	storage< double > sto;
	for ( double x = -100; x < 100; x += 1 )
	{
		sto.add_frame();
		double a = soft_clamped( x, 10.0, 20.0, 0.1 );
		double b = soft_clamped( x, -50.0, 50.0, 0.1 );
		double c = soft_clamped( x, -200.0, 0.0, 0.1 );
		sto[ "x" ] = x;
		sto[ "10..20" ] = a;
		sto[ "-50..50" ] = b;
		sto[ "-200..0" ] = c;
	}
	//std::ofstream( "X:/clamp_test.txt" ) << sto;
}

void linear_regression_test()
{
#if 0
	double step = 1;
	for ( double i = 1; i <= 75.0; i += step ) {
		double tot1 = 0.0;
		double avg = ( i - 1 ) / 2;
		for ( double v = 0; v < i; v += step )
			tot1 += squared( v - avg );
		auto hi = 0.5 * ( i - 1 );
		auto tot1_alg = hi * ( hi + step ) * ( 2 * hi + step ) / ( 3 * step );
		printf( "%.2f: %8.5f %8.5f %8.5f %8.5f\n", i, tot1, tot1_alg, tots, tots_alg  );
	}
#endif

	std::vector< double > x;
	std::vector< double > y;
	for ( int i = -100; i < 50; ++i )
	{
		x.push_back( i );
		y.push_back( i * 2.5 + 4.0 );
	}

	//flut::linear_regression lg( x.begin(), x.end(), y.begin(), y.end() );

	auto lg1 = linear_regression( x.begin(), x.end(), y.begin(), y.end() );
	FLUT_TEST( equals( lg1.coeff[ 1 ], 2.5 ) );
	FLUT_TEST( equals( lg1.coeff[ 0 ], 4.0 ) );

	x.clear();
	y.clear();
	auto xr = make_irange( -50, 100, 2 );
	for ( auto xre : xr )
		y.push_back( xre * -1.5 - 100 );

	auto lg2 = linear_regression( xr, y );
	FLUT_TEST( equals( lg2.coeff[ 1 ], -1.5 ) );
	FLUT_TEST( equals( lg2.coeff[ 0 ], -100.0 ) );

	auto lg3 = linear_regression( -50.0, 2.0, y );
	FLUT_TEST( equals( lg3.coeff[ 1 ], -1.5 ) );
	FLUT_TEST( equals( lg3.coeff[ 0 ], -100.0 ) );

	auto x0 = solve_x( lg3, 0.0 );
	auto x1 = solve_x( lg3, 10.0 );
	auto x2 = solve_x( lg3, -10.0 );
	FLUT_TEST( equals( lg3( x0 ), 0.0 ) );
	FLUT_TEST( equals( lg3( x1 ), 10.0 ) );
	FLUT_TEST( equals( lg3( x2 ), -10.0 ) );
}


void vec_quat_test()
{
	//for ( size_t x = 0; x < 2000; ++x )
	//	if ( is_power_of_two( x ) )
	//		log::debug( x, " is a power of 2" );

	enum TestEnum { Apple, Pear, Banana, Orange };
	flag_set< TestEnum > flg;
	flg.set( Apple, true );
	flg.set( Banana, true );
	flut_logvar4( flg.get( Apple ), flg.get( Pear ), flg.get( Banana ), flg.get( Orange ) );
	flg.set( Banana, false );
	flg.set( Orange, true );
	flut_logvar4( flg.get<Apple>(), flg.get( Pear ), flg.get( Banana ), flg.get( Orange ) );

	std::default_random_engine re( 123 );
	std::uniform_real_distribution<> rd( -10, 10 );

	for ( size_t experiment = 0; experiment < 2; ++experiment )
	{
		std::vector< double > rv( 16 );
		std::generate( rv.begin(), rv.end(), [&]() { return rd( re ); } );

		auto flut_v1 = vec3( rv[0], rv[1], rv[2] );
		auto flut_v2 = vec3( rv[3], rv[4], rv[5] );
		auto flut_x = normalized( flut_v2 - flut_v1 );
		auto flut_y = normalized( cross_product( flut_x, normalized( flut_v2 ) ) );
		auto flut_z = cross_product( flut_x, flut_y );
		flut_logvar3( flut_x.length(), flut_y.length(), flut_z.length() );
		auto flut_q1 = quat_from_axes( flut_x, flut_y, flut_z );
		auto flut_q2 = quat_from_axis_angle( normalized( vec3( rv[6], rv[7], rv[8] ) ), rad( rv[9] ) );
		auto flut_q3 = flut_q1 * flut_q2;
		auto flut_q4 = normalized( flut_q3 );
		flut_logvar3( length(flut_q1), length(flut_q2), length(flut_q3) );
		auto flut_v4 = flut_q4 * flut_v1;
		auto flut_v5 = rotation_vector_from_quat( flut_q4 );

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
			auto flut_qeo = quat_from_euler( rad( rv[0] ), rad( rv[1] ), rad( rv[2] ), flut_eo[ j ] );
			auto scone_qeo = QuatFromEuler( Radian( rv[0] ), Radian( rv[1] ), Radian( rv[2] ), scone_eo[j] );
			compare( flut_qeo, scone_qeo );
		}
	}
}
}
}
