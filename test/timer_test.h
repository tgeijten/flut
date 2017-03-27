#pragma once
#include "flut/timer.hpp"
#include "flut/system_tools.hpp"
#include "flut/system/log.hpp"

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
}
