#include "timer.hpp"

#if defined FLUT_USE_WINDOWS_PERFORMANCE_COUNTER
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <profileapi.h>

namespace flut
{
	long long query_windows_performance_counter_frequency()
	{
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency( &frequency );
		return frequency.QuadPart;
	}

	inline long long query_windows_performance_counter()
	{
		LARGE_INTEGER count;
		QueryPerformanceCounter( &count );
		return count.QuadPart;
	}

	const long long g_frequency = query_windows_performance_counter_frequency();
	const long long g_epoch = query_windows_performance_counter();

	windows_performance_counter_clock::time_point flut::windows_performance_counter_clock::now()
	{
		long long count = query_windows_performance_counter() - g_epoch;
		return time_point( duration( count * static_cast< rep >( period::den ) / g_frequency ) );
	}
}
#endif
