#include "timer.hpp"

#if defined(_MSC_VER) && ( _MSC_VER <= 1800 ) // MSVC 2013 and lower do not have proper chrono support
#	define FLUT_USE_WINDOWS_PERFORMANCE_COUNTER
#	define NOMINMAX
#	define WIN32_LEAN_AND_MEAN
#	include <windows.h>
#	include <profileapi.h>
#else
#	include <chrono>
#endif

namespace flut
{
	timer::timer()
	{
#ifdef FLUT_USE_WINDOWS_PERFORMANCE_COUNTER
		LARGE_INTEGER freq;
		::QueryPerformanceFrequency( &freq );
		frequency = freq.QuadPart;
#endif
		reset();
	}

	void timer::reset()
	{
#ifdef FLUT_USE_WINDOWS_PERFORMANCE_COUNTER
		LARGE_INTEGER e;
		::QueryPerformanceCounter( &e );
		epoch = e.QuadPart;
#else
		epoch = std::chrono::high_resolution_clock::now();
#endif
	}

	timer::seconds_t timer::seconds()
	{
#ifdef FLUT_USE_WINDOWS_PERFORMANCE_COUNTER
		return seconds_t( ticks() ) / frequency;
#else
		return std::chrono::duration< double >( std::chrono::high_resolution_clock::now() - epoch ).count();
#endif
	}

	long long timer::ticks()
	{
#ifdef FLUT_USE_WINDOWS_PERFORMANCE_COUNTER
		LARGE_INTEGER now;
		::QueryPerformanceCounter( &now );
		return now.QuadPart - epoch;
#else
		return ( std::chrono::high_resolution_clock::now() - epoch ).count();
#endif
	}

	flut::timer::clock_ticks_t timer::milliseconds()
	{
#ifdef FLUT_USE_WINDOWS_PERFORMANCE_COUNTER
		return ticks() / ( frequency / 1000 );
#else
		return std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::high_resolution_clock::now() - epoch ).count();
#endif
	}

	flut::timer::clock_ticks_t timer::nanoseconds()
	{
#ifdef FLUT_USE_WINDOWS_PERFORMANCE_COUNTER
		return ticks() / ( frequency / 1000000 );
#else
		return std::chrono::duration_cast<std::chrono::nanoseconds>( std::chrono::high_resolution_clock::now() - epoch ).count();
#endif
	}
}
