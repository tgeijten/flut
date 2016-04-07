#include "flut_test_config.h"
#include "math_test.h"
#include "buffer_test.h"
#include "flut/prop_node.hpp"
#include "flut/system_tools.hpp"

using flut::string;

int main( int argc, char* argv[] )
{
	set_dynamic_log_level( FLUT_LOG_LEVEL_DEBUG );

	flut_logvar2( flut::math::constants<double>::epsilon(), flut::math::constants<double>::relaxed_epsilon() );
	flut_logvar2( flut::math::constants<float>::epsilon(), flut::math::constants<float>::relaxed_epsilon() );

	flut::math::math_test();
	flut::buffer_test();

	flut::prop_node pn;
	pn.set( 1.2 );
	pn.add( "test", 1.2 );
	auto a = pn.get< float >();

	flut::wait_for_key();

	return 0;
}
