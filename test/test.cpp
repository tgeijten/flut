#include "scone/Vec3.h"
#include "scone/Quat.h"
#include "../flut/math/vec3.hpp"
#include "../flut/math/quat.hpp"
#include "../flut/math/random.hpp"
#include "../flut/types.hpp"
#include <conio.h>

using namespace flut;
using namespace flut::math;
using std::cout;
using std::endl;

void compare( const vec3& v1, const scone::Vec3& v2 )
{
	auto diff = abs( v1.x - v2.x ) + abs( v1.y - v2.y ) + abs( v1.z - v2.z );
	cout << "diff=" << diff << " v1=" << v1 << " v2=" << v2 << endl;
}

void compare( const quat& q1, const scone::Quat& q2 )
{
	auto diff = abs( q1.w - q2.W() ) + abs( q1.x - q2.X() ) + abs( q1.y - q2.Y() ) + abs( q1.z - q2.Z() );
	cout << "diff=" << diff << " q1=" << q1 << " q2=" << q2 << endl;
}

int main( int argc, char* argv[] )
{
	auto flut_v1 = vec3( 1, 3, 2 );
	auto flut_v2 = vec3( 4, 3, 9 );
	auto flut_x = normalized( flut_v2 - flut_v1 );
	auto flut_y = normalized( cross_product( flut_x, normalized( flut_v2 ) ) );
	auto flut_z = cross_product( flut_x, flut_y );
	auto flut_q1 = make_quat_from_axes( flut_x, flut_y, flut_z );
	auto flut_v4 = flut_q1 * flut_v1;

	auto scone_v1 = scone::Vec3( 1, 3, 2 );
	auto scone_v2 = scone::Vec3( 4, 3, 9 );
	auto scone_x = ( scone_v2 - scone_v1 ).GetNormalized();
	auto scone_y = ( scone_x.GetCrossProduct( scone_v2.GetNormalized() ) ).GetNormalized();
	auto scone_z = scone_x.GetCrossProduct( scone_y );
	auto scone_q1 = QuatFromAxes( scone_x, scone_y, scone_z );
	auto scone_v4 = scone_q1 * scone_v1;

	compare( flut_v1, scone_v1 );
	compare( flut_v2, scone_v2 );
	compare( flut_x, scone_x );
	compare( flut_y, scone_y );
	compare( flut_z, scone_z );
	compare( flut_q1, scone_q1 );
	compare( flut_v4, scone_v4 );

	_getch();

	return 0;
}
