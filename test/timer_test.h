#pragma once
#include "flut/timer.hpp"
#include "flut/system_tools.hpp"
#include "flut/system/log.hpp"
#include "flut/system/profiler.hpp"

namespace flut
{
	void timer_test()
	{
		long long delta = 0;
		long long prev = 0;
		timer t;
		const int samples = 10000000;
		for ( int i = 0; i < samples; ++i )
		{
			long long tick1 = t.ticks();
			long long tick2 = t.ticks();
			delta += tick2 - tick1;
		}
		
		flut::log::info( setfixed( 3 ), "Time measure takes ", (double)delta / samples, "ns" );
	};

	void profile1()
	{
		FLUT_PROFILE_FUNCTION;
		sleep( 1 );
	}

	void profile2()
	{
		FLUT_PROFILE_FUNCTION;
		sleep( 2 );
		profile1();
	}

	void profile3()
	{
		FLUT_PROFILE_FUNCTION;
		sleep( 3 );
		profile2();
	}

	void profile_all()
	{
		FLUT_PROFILE_FUNCTION;
		profile1();
		profile2();
		profile3();
	}

	void profile_test()
	{
		FLUT_PROFILE_RESET;

		for ( int i = 0; i < 10; ++i )
			profile_all();
		profile1();
		profile2();
		profile3();

		flut::log::info( FLUT_PROFILE_REPORT );
	}
}
