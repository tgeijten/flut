#include "flut_test_config.h"
#include "math_test.h"
#include "buffer_test.h"

int main( int argc, char* argv[] )
{
	set_dynamic_log_level( FLUT_LOG_LEVEL_DEBUG );

	flut_logvar2( flut::math::constants<double>::epsilon(), flut::math::constants<double>::relaxed_epsilon() );
	flut_logvar2( flut::math::constants<float>::epsilon(), flut::math::constants<float>::relaxed_epsilon() );

	std::stringstream str( "1 2 3" );
	flut::math::vec3 v2;
	//str >> v2;

	flut::math::math_test();
	flut::buffer_test();

	_getch();

	return 0;
}
