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
#include "factory_test.h"
#include "container_test.h"
#include "timer_test.h"
#include "flut/system/profiler.hpp"
#include "data_test.h"
#include "delay_test.h"
#include "filter_test.h"

using flut::string;

int main( int argc, char* argv[] )
{
	flut::log::stream_sink str( flut::log::info_level, std::cout );
	flut::log::add_sink( &str );

	try
	{
		flut::filter_test();
		flut::delay_test();

		flut::timer_test();

#ifdef FLUT_ENABLE_PROFILER
		flut::profile_test();
#endif
		flut::stopwatch sw;

		flut::container_test();
		sw.add_measure( "container" );

		flut::data_test();
		sw.add_measure( "data" );

		flut::factory_test();
		sw.add_measure( "factory" );

		flut::prop_node_test();
		sw.add_measure( "prop_node" );

		flut::string_test();
		sw.add_measure( "string" );

		flut::buffer_test();
		sw.add_measure( "buffer" );

		flut::math::optional_test();
		flut::math::clamp_test();
		flut::math::linear_regression_test();
		flut::math::math_test();
		flut::math::function_test();
		flut::math::angle_test();
		flut::math::vec_quat_test();
		sw.add_measure( "math" );

		auto pn = sw.get_report();
		flut::log::info( pn );
	}
	catch ( std::exception& e )
	{
		std::cout << e.what();				
	}

	int i = flut::test_framework::get_instance().report();

#if FLUT_IS_DEBUG_BUILD && defined( FLUT_COMP_MSVC )
	flut::wait_for_key();
#endif

	return i;
}
