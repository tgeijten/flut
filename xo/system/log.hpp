#pragma once

#ifndef FLUT_STATIC_LOG_LEVEL
#	define FLUT_STATIC_LOG_LEVEL FLUT_LOG_LEVEL_TRACE
#endif

#include "flut/string_tools.hpp"
#include <iostream>
#include <functional>
#include <stdarg.h>

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

#define flut_trace_call( function_ ) flut::log::trace( "--> "#function_ ); function_; flut::log::trace( "<-- "#function_ )

namespace flut
{
	struct setfixed
	{
		setfixed( int decimals ) : decimals_( decimals ) {};
		friend std::ostream& operator<<( std::ostream& str, const setfixed& sf ) { return str << std::fixed << std::setprecision( sf.decimals_ ); }
		int decimals_;
	};

	namespace log
	{
		enum level { trace_level = FLUT_LOG_LEVEL_TRACE, debug_level, info_level, warning_level, error_level, critical_level, never_log_level };

		// output sink
		class sink;
		FLUT_API void add_sink( sink* s );
		FLUT_API void remove_sink( sink* s );

		// dynamic log level
		FLUT_API void set_global_log_level( level l );
		FLUT_API level get_global_log_level();
		FLUT_API bool test_log_level( level l );

		// log independent of level
		FLUT_API void log_string( level l, const string& str );
		FLUT_API void log_vstring( level l, const char* format, va_list list );
		inline void log_stream( level l, std::stringstream& msg ) { log_string( l, msg.str() ); }
		template< typename T, typename... Args > void log_stream( level l, std::stringstream& str, T var, const Args&... args ) { str << var; log_stream( l, str, args... ); }

		// log at specified level
		template< typename... Args > void message( level l, const Args&... args ) { if ( test_log_level( l ) ) { std::stringstream str; log_stream( l, str, args... ); }	}
		inline void messagef( level l, const char* format, ... ) { va_list va; va_start( va, format ); log_vstring( l, format, va ); va_end( va ); }

#if ( FLUT_STATIC_LOG_LEVEL <= FLUT_LOG_LEVEL_TRACE )
		template< typename... Args > void trace( const Args&... args ) { message( trace_level, args... ); }
		inline void tracef( const char* format, ... ) { va_list va; va_start( va, format ); log_vstring( trace_level, format, va ); va_end( va ); }
#else
		template< typename... Args > void trace( const Args&... args ) {}
		inline void tracef( const char* format, ... ) {}
#endif

#if ( FLUT_STATIC_LOG_LEVEL <= FLUT_LOG_LEVEL_DEBUG )
		template< typename... Args > void debug( const Args&... args ) { message( debug_level, args... ); }
		inline void debugf( const char* format, ... ) { va_list va; va_start( va, format ); log_vstring( debug_level, format, va ); va_end( va ); }
#else
		template< typename... Args > void debug( const Args&... args ) {}
		inline void debugf( const char* format, ... ) {}
#endif

#if ( FLUT_STATIC_LOG_LEVEL <= FLUT_LOG_LEVEL_INFO )
		template< typename... Args > void info( const Args&... args ) {	message( info_level, args... ); }
		inline void infof( const char* format, ... ) { va_list va; va_start( va, format ); log_vstring( info_level, format, va ); va_end( va ); }
#else
		template< typename... Args > void info( const Args&... args ) {}
		inline void infof( const char* format, ... ) {}
#endif

#if ( FLUT_STATIC_LOG_LEVEL <= FLUT_LOG_LEVEL_WARNING )
		template< typename... Args > void warning( const Args&... args ) { message( warning_level, args... ); }
		inline void warningf( const char* format, ... ) { va_list va; va_start( va, format ); log_vstring( warning_level, format, va ); va_end( va ); }
#else
		template< typename... Args > void warning( const Args&... args ) {}
		inline void warningf( const char* format, ... ) {}
#endif

#if ( FLUT_STATIC_LOG_LEVEL <= FLUT_LOG_LEVEL_ERROR )
		template< typename... Args > void error( const Args&... args ) { message( error_level, args... ); }
		inline void errorf( const char* format, ... ) { va_list va; va_start( va, format ); log_vstring( error_level, format, va ); va_end( va ); }
#else
		template< typename... Args > void error( const Args&... args ) {}
		inline void errorf( const char* format, ... ) {}
#endif

#if ( FLUT_STATIC_LOG_LEVEL <= FLUT_LOG_LEVEL_CRITICAL )
		template< typename... Args > void critical( const Args&... args ) { message( critical_level, args... ); }
		inline void criticalf( const char* format, ... ) { va_list va; va_start( va, format ); log_vstring( critical_level, format, va ); va_end( va ); }
#else
		template< typename... Args > void critical( const Args&... args ) {}
		inline void criticalf( const char* format, ... ) {}
#endif
	}
}
