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

	std::vector< double > work_result;

	void do_work( int amount )
	{
		FLUT_PROFILE_FUNCTION;
		double sum = 0.0;
		for ( int x = 0; x < amount; ++x )
			sum += sqrt( double( x ) );
		work_result.push_back( sum );
	}

	void profile1()
	{
		FLUT_PROFILE_FUNCTION;
		do_work( 10 );
	}

	void profile2( int i )
	{
		FLUT_PROFILE_FUNCTION;
		do_work( 100 );
		if ( i % 5 < 3 )
			profile2( i + 1 );
		profile1();
	}

	void profile3( int i )
	{
		FLUT_PROFILE_FUNCTION;
		do_work( 1000 );
		profile1();
		profile2( i );
		if ( i % 7 < 3 )
			profile3( i + 1 );
	}

	void profile_test()
	{
		FLUT_PROFILE_RESET;

		for ( int i = 0; i < 100000; ++i )
			profile3( i );

		flut::log::info( FLUT_PROFILE_REPORT );
	}
}
