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

		/// get elapsed number of CPU ticks
		clock_ticks_t ticks();

		/// get elapsed time in seconds
		seconds_t seconds();

		/// get elapsed number of nanoseconds
		clock_ticks_t milliseconds();

		/// get elapsed number of nanoseconds
		clock_ticks_t nanoseconds();

	private:
#ifdef FLUT_USE_WINDOWS_PERFORMANCE_COUNTER
		clock_ticks_t epoch;
		clock_ticks_t frequency;
#else
		std::chrono::time_point< std::chrono::high_resolution_clock, std::chrono::high_resolution_clock::duration > epoch;
#endif
	};
}
