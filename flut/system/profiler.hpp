#pragma once

#include "types.hpp"
#include <utility>
#include <map>
#include "flut/timer.hpp"
#include "flut/prop_node.hpp"

#ifdef FLUT_COMP_MSVC
#	pragma warning( push )
#	pragma warning( disable: 4251 )
#endif

#if FLUT_USE_PROFILER
#	define FLUT_PROFILE_FUNCTION flut::profile_section unique_profile_section( __FUNCTION__ )
#	define FLUT_PROFILE_SCOPE( scope_name_arg ) flut::profile_section unique_profile_section( scope_name_arg )
#	define FLUT_PROFILE_RESET flut::profiler::instance().reset()
#	define FLUT_PROFILE_REPORT flut::profiler::instance().report()
#else
#	define FLUT_PROFILE_FUNCTION
#	define FLUT_PROFILE_SCOPE( scope_name_arg )
#	define FLUT_PROFILE_RESET
#	define FLUT_PROFILE_REPORT flut::prop_node()
#endif

namespace flut
{
	class FLUT_API profiler
	{
	public:
		struct section
		{
			section( section* p, const char* n ) : parent( p ), name( n ), inclusive_time( 0 ), overhead( 0 ), samples( 0 ) {}
			section( const section& ) = delete;
			section& operator=( const section& ) = delete;
			section* parent;
			const char* name;
			nanoseconds_t inclusive_time;
			nanoseconds_t overhead;
			size_t samples;
			nanoseconds_t epoch;
			std::vector< u_ptr< section > > children;
		};

		void reset();
		section* start_section( const char* name );
		void end_section();
		nanoseconds_t now() { return timer_.nanoseconds(); }
		prop_node report();
		static profiler& instance() { return instance_; }

	private:
		profiler() { reset(); }
		nanoseconds_t report_section( const section* s, prop_node& pn );

		timer timer_;
		static profiler instance_;
		u_ptr< section > root_;
		section* current_section_;
	};

	struct FLUT_API profile_section
	{
		profile_section( const char* name ) { profiler::instance().start_section( name ); }
		~profile_section() { profiler::instance().end_section(); }
	};
}

#ifdef FLUT_COMP_MSVC
#	pragma warning( pop )
#endif
