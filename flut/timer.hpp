#pragma once

#include "system/platform.hpp"

#if defined (_MSC_VER ) && ( _MSC_VER <= 1800 ) // MSVC 2013 and lower do not have proper chrono support
#	define FLUT_USE_WINDOWS_PERFORMANCE_COUNTER
#else
#	include <chrono>
#endif

namespace flut
{
	class FLUT_API timer
	{
	public:
		typedef long long clock_ticks_t;
		typedef double seconds_t;

		/// constructor, resets timer
		timer();

		/// reset timer
		void reset();

		/// get elapsed time in seconds
		double seconds();

		/// get elapsed number of CPU ticks
		clock_ticks_t ticks();

	private:
#ifdef FLUT_USE_WINDOWS_PERFORMANCE_COUNTER
		clock_ticks_t epoch;
		seconds_t ticks_to_seconds;
#else
		std::chrono::time_point< std::chrono::high_resolution_clock, std::chrono::high_resolution_clock::duration > epoch;
#endif
	};
}
