#pragma once

#include <ostream>
#include "../string_tools.hpp"
#include <string>
#include <iostream>

#define flut_do_periodic( interval_, statement_ ) { static local_count_ = 0; if ( local_count_++ % interval_ == 0 ) { statement_; } }

#define FLUT_LOG_LEVEL_ALL 1
#define FLUT_LOG_LEVEL_TRACE 1
#define FLUT_LOG_LEVEL_DEBUG 2
#define FLUT_LOG_LEVEL_INFO 3
#define FLUT_LOG_LEVEL_WARNING 4
#define FLUT_LOG_LEVEL_ERROR 5
#define FLUT_LOG_LEVEL_CRITICAL 6
#define FLUT_LOG_LEVEL_NONE 7

#ifndef FLUT_LOG_LEVEL
#define FLUT_LOG_LEVEL FLUT_LOG_LEVEL_INFO
#endif

#ifndef FLUT_LOG_OUTPUT_STREAM
#define FLUT_LOG_OUTPUT_STREAM std::cout
#endif

#define flut_logvar( var_ ) FLUT_LOG_OUTPUT_STREAM << #var_"=" << var_ << std::endl
#define flut_logvar2( var1_, var2_ ) FLUT_LOG_OUTPUT_STREAM << #var1_"=" << var1_ << "\t" << #var2_"=" << var2_ << std::endl
#define flut_logvar3( var1_, var2_, var3_ ) FLUT_LOG_OUTPUT_STREAM << #var1_"=" << var1_ << "\t" << #var2_"=" << var2_ << "\t" << #var3_"=" << var3_ << std::endl
#define flut_logvar4( var1_, var2_, var3_, var4_ ) FLUT_LOG_OUTPUT_STREAM << #var1_"=" << var1_ << "\t" << #var2_"=" << var2_ << "\t" << #var3_"=" << var3_ << "\t" << #var4_"=" << var4_ << std::endl

namespace flut
{
	namespace log
	{
		inline void log_output() { std::cerr << std::endl; }

		template < typename T, typename... Args >
		void log_output( T var, const Args&... args )
		{ FLUT_LOG_OUTPUT_STREAM << var; log_output( args... ); }
	}
}

namespace flut
{
	namespace log
	{
		template< typename... Args > void trace( const Args&... args ) {
#if ( FLUT_LOG_LEVEL <= FLUT_LOG_LEVEL_TRACE )
			log_output( args... );
#endif
		}

		template< typename... Args > void debug( const Args&... args ) {
#if ( FLUT_LOG_LEVEL <= FLUT_LOG_LEVEL_DEBUG )
			log_output( args... );
#endif
		}

		template< typename... Args > void info( const Args&... args ) {
#if ( FLUT_LOG_LEVEL <= FLUT_LOG_LEVEL_INFO )
			log_output( args... );
#endif
		}

		template< typename... Args > void warning( const Args&... args ) {
#if ( FLUT_LOG_LEVEL <= FLUT_LOG_LEVEL_WARNING )
			log_output( args... );
#endif
		}

		template< typename... Args > void error( const Args&... args ) {
#if ( FLUT_LOG_LEVEL <= FLUT_LOG_LEVEL_ERROR )
			log_output( args... );
#endif
		}

		template< typename... Args > void critical( const Args&... args ) {
#if ( FLUT_LOG_LEVEL <= FLUT_LOG_LEVEL_CRITICAL )
			log_output( args... );
#endif
		}
	}
}
