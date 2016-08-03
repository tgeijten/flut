#pragma once

#ifndef FLUT_STATIC_LOG_LEVEL
#	define FLUT_STATIC_LOG_LEVEL FLUT_LOG_LEVEL_TRACE
#endif

#include <iostream>
#include "flut/string_tools.hpp"

#define FLUT_LOG_LEVEL_ALL 1
#define FLUT_LOG_LEVEL_TRACE 1
#define FLUT_LOG_LEVEL_DEBUG 2
#define FLUT_LOG_LEVEL_INFO 3
#define FLUT_LOG_LEVEL_WARNING 4
#define FLUT_LOG_LEVEL_ERROR 5
#define FLUT_LOG_LEVEL_CRITICAL 6
#define FLUT_LOG_LEVEL_NONE 7

#define flut_do_periodic( interval_, statement_ ) { static local_count_ = 0; if ( local_count_++ % interval_ == 0 ) { statement_; } }

#define flut_logvar( var_ ) flut::log::trace( #var_"=", var )
#define flut_logvar2( var1_, var2_ ) flut::log::trace( #var1_"=", var1_, "\t", #var2_"=", var2_ )
#define flut_logvar3( var1_, var2_, var3_ ) flut::log::trace( #var1_"=", var1_, "\t", #var2_"=", var2_, "\t", #var3_"=", var3_ )
#define flut_logvar4( var1_, var2_, var3_, var4_ ) flut::log::trace( #var1_"=", var1_, "\t", #var2_"=", var2_, "\t", #var3_"=", var3_, "\t", #var4_"=", var4_ )

namespace flut
{
	namespace log
	{
		enum level { trace_level = FLUT_LOG_LEVEL_TRACE, debug_level, info_level, warning_level, error_level, critical_level };

		FLUT_API void set_level( level l );
		FLUT_API void set_level( int l );
		FLUT_API level get_level();

		inline void log_output() { FLUT_LOG_OUTPUT_STREAM << std::endl; }
		template< typename T, typename... Args > void log_output( T var, const Args&... args )
		{ FLUT_LOG_OUTPUT_STREAM << var; log_output( args... ); }

		template< typename... Args > void message( level l, const Args&... args ) {
			if ( FLUT_STATIC_LOG_LEVEL <= l && get_level() <= l ) log_output( args... );
		}

		template< typename... Args > void trace( const Args&... args ) {
#if ( FLUT_STATIC_LOG_LEVEL <= FLUT_LOG_LEVEL_TRACE )
			if ( get_level() <= FLUT_LOG_LEVEL_TRACE ) log_output( args... );
#endif
		}

		template< typename... Args > void debug( const Args&... args ) {
#if ( FLUT_STATIC_LOG_LEVEL <= FLUT_LOG_LEVEL_DEBUG )
			if ( get_level() <= FLUT_LOG_LEVEL_DEBUG ) log_output( args... );
#endif
		}

		template< typename... Args > void info( const Args&... args ) {
#if ( FLUT_STATIC_LOG_LEVEL <= FLUT_LOG_LEVEL_INFO )
			if ( get_level() <= FLUT_LOG_LEVEL_INFO ) log_output( args... );
#endif
		}

		template< typename... Args > void warning( const Args&... args ) {
#if ( FLUT_STATIC_LOG_LEVEL <= FLUT_LOG_LEVEL_WARNING )
			if ( get_level() <= FLUT_LOG_LEVEL_WARNING ) log_output( args... );
#endif
		}

		template< typename... Args > void error( const Args&... args ) {
#if ( FLUT_STATIC_LOG_LEVEL <= FLUT_LOG_LEVEL_ERROR )
			if ( get_level() <= FLUT_LOG_LEVEL_ERROR ) log_output( args... );
#endif
		}

		template< typename... Args > void critical( const Args&... args ) {
#if ( FLUT_STATIC_LOG_LEVEL <= FLUT_LOG_LEVEL_CRITICAL )
			if ( get_level() <= FLUT_LOG_LEVEL_CRITICAL ) log_output( args... );
#endif
		}
	}
}
