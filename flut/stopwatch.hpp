#pragma once

#include "system/types.hpp"
#include "timer.hpp"
#include "system/log.hpp"
#include "prop_node.hpp"

#ifdef FLUT_COMP_MSVC
#	pragma warning( push )
#	pragma warning( disable: 4251 )
#endif

namespace flut
{
	class FLUT_API stopwatch
	{
	public:
		typedef std::pair< std::string, timer::clock_ticks_t > measure_t;

		stopwatch() : internal_measure_( 0 ), timer_() { start_first_measure(); }
		~stopwatch() {}

		void start_first_measure() { epoch_ = timer_.ticks(); }
		void add_measure( const string& s );

		prop_node get_report( int decimals = 6 );
		
	private:
		timer::clock_ticks_t epoch_;
		std::vector< measure_t > measures_;
		timer::clock_ticks_t internal_measure_;
		timer timer_;
	};
}

#ifdef FLUT_COMP_MSVC
#	pragma warning( pop )
#endif
