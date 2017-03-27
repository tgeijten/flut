#pragma once

#include "types.hpp"
#include <utility>
#include <map>
#include "flut/timer.hpp"
#include "flut/prop_node.hpp"

namespace flut
{
	class profiler
	{
	public:
		struct section
		{
			section( section* p, const char* n ) : parent( p ), name( n ), inclusive_time( 0 ), overhead( 0 ), samples( 0 ) {}
			section* parent;
			const char* name;
			nanoseconds_t inclusive_time;
			nanoseconds_t overhead;
			size_t samples;
			nanoseconds_t epoch;
			std::vector< u_ptr< section > > children;
		};

		static profiler& instance() { return instance(); }
		section* start_section( const char* name );
		void end_section();
		nanoseconds_t now() { return timer_.nanoseconds(); }
		prop_node report();

	private:
		profiler() : root_( nullptr, "" ), current_section_( &root_ ) {}
		nanoseconds_t report_section( const section* s, prop_node& pn );

		timer timer_;
		static profiler global_instance_;
		std::map< std::pair< section*, const char* >, section* > segments_;
		section root_;
		section* current_section_;
	};

	class profile_section
	{
		profile_section( const char* name ) { profiler::instance().start_section( name ); }
		~profile_section() { profiler::instance().end_section(); }
	};
}
