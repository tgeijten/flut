#pragma once

#ifdef FLUT_ENABLE_PROFILER
#	include "flut/system/profiler.hpp"
#	define FLUT_PROFILE_FUNCTION ::flut::scoped_section_profiler _PROFILE_SECTION_( __FUNCTION__ )
#	define FLUT_PROFILE_SCOPE( scope_name_arg ) ::flut::scoped_section_profiler _PROFILE_SECTION_( scope_name_arg )
inline void flut_profiler_reset() { ::flut::profiler::instance().reset(); }
inline void flut_profiler_log_report( ::flut::log::level l ) { ::flut::log::message( l, ::flut::profiler::instance().report() ); }
#else
#	define FLUT_PROFILE_FUNCTION
#	define FLUT_PROFILE_SCOPE( scope_name_arg )
inline void flut_profiler_reset() {}
inline void flut_profiler_log_report( ::flut::log::level l ) {}
#endif
