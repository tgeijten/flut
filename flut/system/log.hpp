#pragma once

#ifndef FLUT_STATIC_LOG_LEVEL
#	define FLUT_STATIC_LOG_LEVEL FLUT_LOG_LEVEL_TRACE
#endif

#include "flut/string_tools.hpp"
#include <iostream>
#include <functional>

#define FLUT_LOG_LEVEL_ALL 1
#define FLUT_LOG_LEVEL_TRACE 1
#define FLUT_LOG_LEVEL_DEBUG 2
#define FLUT_LOG_LEVEL_INFO 3
#define FLUT_LOG_LEVEL_WARNING 4
#define FLUT_LOG_LEVEL_ERROR 5
#define FLUT_LOG_LEVEL_CRITICAL 6
#define FLUT_LOG_LEVEL_NONE 7

#define flut_do_periodic( interval_, statement_ ) { static local_count_ = 0; if ( local_count_++ % interval_ == 0 ) { statement_; } }

#define flut_logvar( var_ ) flut::log::trace( #var_"=", var_ )
#define flut_logvar2( var1_, var2_ ) flut::log::trace( #var1_"=", var1_, "\t", #var2_"=", var2_ )
#define flut_logvar3( var1_, var2_, var3_ ) flut::log::trace( #var1_"=", var1_, "\t", #var2_"=", var2_, "\t", #var3_"=", var3_ )
#define flut_logvar4( var1_, var2_, var3_, var4_ ) flut::log::trace( #var1_"=", var1_, "\t", #var2_"=", var2_, "\t", #var3_"=", var3_, "\t", #var4_"=", var4_ )

namespace flut
{
	namespace log
	{
		enum level { trace_level = FLUT_LOG_LEVEL_TRACE, debug_level, info_level, warning_level, error_level, critical_level, never_log_level };

		/// output sink
		class sink;
		FLUT_API void add_sink( sink* s );
		FLUT_API void remove_sink( sink* s );

		FLUT_API void update_lowest_log_level();
		FLUT_API bool test_log_level( level l );

		FLUT_API void log_output( level l, std::stringstream& msg );

		template< typename T, typename... Args > void log_output( level l, std::stringstream& str, T var, const Args&... args )
		{ str << var; log_output( l, str, args... ); }

		template< typename... Args > void message( level l, const Args&... args )
		{ if ( test_log_level( l ) ) { std::stringstream str; log_output( l, str, args... ); }	}

		template< typename... Args > void trace( const Args&... args ) {
#if ( FLUT_STATIC_LOG_LEVEL <= FLUT_LOG_LEVEL_TRACE )
			message( trace_level, args... );
#endif
		}

		template< typename... Args > void debug( const Args&... args ) {
#if ( FLUT_STATIC_LOG_LEVEL <= FLUT_LOG_LEVEL_DEBUG )
			message( debug_level, args... );
#endif
		}

		template< typename... Args > void info( const Args&... args ) {
#if ( FLUT_STATIC_LOG_LEVEL <= FLUT_LOG_LEVEL_INFO )
			message( info_level, args... );
#endif
		}

		template< typename... Args > void warning( const Args&... args ) {
#if ( FLUT_STATIC_LOG_LEVEL <= FLUT_LOG_LEVEL_WARNING )
			message( warning_level, args... );
#endif
		}

		template< typename... Args > void error( const Args&... args ) {
#if ( FLUT_STATIC_LOG_LEVEL <= FLUT_LOG_LEVEL_ERROR )
			message( error_level, args... );
#endif
		}

		template< typename... Args > void critical( const Args&... args ) {
#if ( FLUT_STATIC_LOG_LEVEL <= FLUT_LOG_LEVEL_CRITICAL )
			message( critical_level, args... );
#endif
		}
	}
}
