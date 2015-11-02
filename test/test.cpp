#include "../flut/math/vec3.hpp"
#include "../flut/math/quat.hpp"
#include "../flut/math/random.hpp"
#include "../flut/types.hpp"

using namespace flut;
using namespace flut::math;

int main( int argc, char* argv[] )
{
	random< real_t > rng( 123 );

	auto vrnd = vec3( rng.uni( -1, 1 ), rng.uni( -1, 1 ), rng.uni( -1, 1 ) );
	auto v1 = vec3( 1, 2, 3 );
	auto v2 = vec3( 4, 5, 6 );
	auto v3 = v2 - v1;
	auto q1 = make_quat_from_axes( v1, v2, v3 );
	auto v4 = q1 * v1;

	return 0;
}
