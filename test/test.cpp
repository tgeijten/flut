#include "test.h"
#include "math_test.h"
#include "buffer_test.h"
#include "flut/prop_node.hpp"
#include "flut/system_tools.hpp"
#include "prop_node_test.h"
#include "flut/stopwatch.hpp"
#include "flut/system/test_framework.hpp"
#include "string_test.h"
#include "flut/dictionary.hpp"
#include "flut/system/log_sink.hpp"

using flut::string;

int main( int argc, char* argv[] )
{
	flut::log::stream_sink str( flut::log::info_level, std::cout );
	flut::log::add_sink( &str );

	try
	{
		enum fruit { no_fruit, appel, peer, banaan };
		auto fruit_dict = flut::dictionary< fruit >( { { appel, "appel" }, { peer, "peer" }, { banaan, "banaan" } } );

		string s = "peer2";
		switch ( fruit_dict( s, no_fruit ) )
		{
		case appel: cout << "we've got an apple"; break;
		case peer: cout << "we've got a peario"; break;
		case banaan: cout << "banana over here!"; break;
		default: cout << "Could not find this fruit"; break;
		}

		auto str = flut::split_str( "appel; peer,,, banaan", ";. " );

		flut_logvar2( flut::math::constants<double>::epsilon(), flut::math::constants<double>::relaxed_epsilon() );
		flut_logvar2( flut::math::constants<float>::epsilon(), flut::math::constants<float>::relaxed_epsilon() );

		flut::stopwatch sw;

		flut::prop_node_test();
		sw.add_measure( "propnode" );

		flut::string_test();
		sw.add_measure( "string" );

		flut::buffer_test();
		sw.add_measure( "buffer" );

		flut::math::function_test();
		flut::math::angle_test();
		flut::math::vec_quat_test();
		sw.add_measure( "math" );

		flut::log::info( sw.get_report() );
	}
	catch ( std::exception& e )
	{
		std::cout << e.what();				
	}

	return flut::test_framework::get_instance().report();
}
