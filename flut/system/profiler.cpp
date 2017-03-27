#include "profiler.hpp"
#include <algorithm>

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
		auto it = std::find_if( current_section_->children.begin(), current_section_->children.end(), [&]( u_ptr< section >& s ) { return s->name == name; } );
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
		current_section_->total_time += now() - current_section_->epoch;
		current_section_ = current_section_->parent;
	}

	prop_node profiler::report()
	{
		root_->total_time = now() - root_->epoch;
		prop_node pn;
		report_section( root_.get(), pn );
		return pn;
	}

	void profiler::report_section( section* s, prop_node& pn )
	{
		double rel_total = 100.0 * s->total_time / root_->total_time;
		double rel_ex = 100.0 * s->exclusive_time() / root_->total_time;
		double rel_over = 100.0 * s->total_overhead() / root_->total_time;

		pn.set_value( stringf( "%6.2f (%5.2f exclusive %.2f overhead)", rel_total, rel_ex, rel_over ) );

		std::sort( s->children.begin(), s->children.end(), [&]( u_ptr< section >& s1, u_ptr< section >& s2 ) { return s1->total_time > s2->total_time; } );

		for ( auto& c : s->children )
			report_section( c.get(), pn.push_back( c->name ) );
	}
}
