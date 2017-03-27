#pragma once

#include "system/platform.hpp"
#include <chrono>

#if defined (_MSC_VER ) && ( _MSC_VER <= 1800 ) // MSVC 2013 and lower do not have proper chrono support
#	define FLUT_USE_WINDOWS_PERFORMANCE_COUNTER
#endif

#ifdef FLUT_COMP_MSVC
#	pragma warning( push )
#	pragma warning( disable: 4251 )
#endif

namespace flut
{
#if defined FLUT_USE_WINDOWS_PERFORMANCE_COUNTER
	struct windows_performance_counter_clock
	{
		typedef long long rep;
		typedef std::nano period;
		typedef std::chrono::duration< rep, period > duration;
		typedef std::chrono::time_point< windows_performance_counter_clock > time_point;
		static const bool is_steady = true;
		static time_point now();
	};
#endif

	class FLUT_API timer
	{
	public:
#if defined FLUT_USE_WINDOWS_PERFORMANCE_COUNTER
		typedef windows_performance_counter_clock timer_t;
#else
		typedef std::chrono::high_resolution_clock timer_t;
#endif
		timer() : epoch( timer_t::now() ) {}
		void reset() { epoch = timer_t::now(); }

		double seconds() { return std::chrono::duration< double, std::ratio< 1 > >( elapsed() ).count(); }
		double minutes() { return std::chrono::duration< double, std::ratio< 60 > >( elapsed() ).count(); }
		double hours() { return std::chrono::duration< double, std::ratio< 3600 > >( elapsed() ).count(); }

		long long milliseconds() { return std::chrono::duration_cast< std::chrono::milliseconds >( elapsed() ).count(); }
		long long microseconds() { return std::chrono::duration_cast< std::chrono::microseconds >( elapsed() ).count(); }
		long long nanoseconds() { return std::chrono::duration_cast< std::chrono::nanoseconds >( elapsed() ).count(); }
		long long ticks() { return elapsed().count(); }

	private:
		timer_t::time_point epoch;
		timer_t::duration elapsed() { return timer_t::now() - epoch; }
	};
}

#ifdef FLUT_COMP_MSVC
#	pragma warning( pop )
#endif
