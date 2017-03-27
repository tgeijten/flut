#include "profiler.hpp"

namespace flut
{
profiler profiler::global_instance_;

	profiler::section* profiler::start_section( const char* name )
	{
		auto t = now();
		auto it = segments_.find( std::make_pair( current_section_, name ) );
		if ( it == segments_.end() )
		{
			section* s = new section( current_section_, name );
			segments_[ std::make_pair( current_section_, name ) ] = s;
			current_section_ = s;
		}
		else current_section_ = it->second;

		current_section_->epoch = now();
		current_section_->overhead += current_section_->epoch - t;

		return current_section_;
	}

	void profiler::end_section()
	{
		current_section_->inclusive_time += now() - current_section_->epoch;
		current_section_ = current_section_->parent;
	}

	prop_node profiler::report()
	{
		prop_node pn;
		report_section( &root_, pn );
		return pn;
	}

	nanoseconds_t profiler::report_section( const section* s, prop_node& pn )
	{
		nanoseconds_t children_time = 0;
		for ( auto it = s->children.begin(); it != s->children.end(); ++it )
			children_time += report_section( it->get(), pn.push_back( s->name ) );

		pn.set_value( stringf( "%6.2f (%5.2f exclusive)", 100.0 * s->inclusive_time / root_.inclusive_time, 100.0 * ( s->inclusive_time - children_time ) / root_.inclusive_time ) );

		return s->inclusive_time;
	}
}
