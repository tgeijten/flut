#include "test.h"
#include "math_test.h"
#include "buffer_test.h"
#include "flut/prop_node.hpp"
#include "flut/system_tools.hpp"
#include "prop_node_test.h"
#include "flut/stopwatch.hpp"

using flut::string;

int main( int argc, char* argv[] )
{
	try
	{
		flut::log::set_level( FLUT_LOG_LEVEL_TRACE );
		cout << flut::log::get_level();

		auto str = flut::split_str( "appel; peer,,, banaan", ";. " );

		flut_logvar2( flut::math::constants<double>::epsilon(), flut::math::constants<double>::relaxed_epsilon() );
		flut_logvar2( flut::math::constants<float>::epsilon(), flut::math::constants<float>::relaxed_epsilon() );

		flut::stopwatch sw;

		flut::prop_node_test();
		sw.add_measure( "propnode" );

		flut::buffer_test();
		sw.add_measure( "buffer" );

		flut::math::function_test();
		flut::math::angle_test();
		flut::math::vec_quat_test();
		sw.add_measure( "math" );

		flut::log::info( std::fixed, sw.get_report() );
	}
	catch ( std::exception& e )
	{
		std::cout << e.what();				
	}

	return 0;
}
