#include "profiler.hpp"

namespace flut
{
profiler profiler::instance_;

	void profiler::reset()
	{
		root_ = u_ptr< section >( new section( nullptr, "root" ) );
		current_section_ = root_.get();
		root_->epoch = now();
	}

	profiler::section* profiler::start_section( const char* name )
	{
		auto t = now();
		auto it = std::find_if( current_section_->children.begin(), current_section_->children.end(), [&]( u_ptr< section >& s ) { return strcmp( s->name, name ) == 0; } );
		if ( it == current_section_->children.end() )
		{
			current_section_->children.emplace_back( new section( current_section_, name ) );
			current_section_ = current_section_->children.back().get();
		}
		else current_section_ = it->get();

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
		root_->inclusive_time = now() - root_->epoch;
		prop_node pn;
		report_section( root_.get(), pn );
		return pn;
	}

	nanoseconds_t profiler::report_section( const section* s, prop_node& pn )
	{
		nanoseconds_t children_time = 0;
		for ( auto& c : s->children )
			children_time += report_section( c.get(), pn.push_back( c->name ) );

		pn.set_value( stringf( "%6.2f (%5.2f exclusive)", 100.0 * s->inclusive_time / root_->inclusive_time, 100.0 * ( s->inclusive_time - children_time ) / root_->inclusive_time ) );

		return s->inclusive_time;
	}
}
