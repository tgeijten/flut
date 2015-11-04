#pragma once

#include <iosfwd>
#include <ostream>
#include "../string_tools.hpp"

#define fluc_do_periodic( interval_, statement_ ) { static local_count_ = 0; if ( local_count_++ % interval_ == 0 ) { statement_; } }

#define FLUC_LOG_TRACE_LEVEL 1
#define FLUC_LOG_INFO_LEVEL 2

#ifndef FLUC_LOG_LEVEL
#define FLUC_LOG_LEVEL info_level
#endif

#ifndef FLUC_LOG_OUTPUT_STREAM
#define FLUC_LOG_OUTPUT_STREAM std::cout
#endif

#define flut_logvar( var_ ) std::cout << #var_"=" << var_ << std::endl
#define flut_logvar2( var1_, var2_ ) std::cout << #var1_"=" << var1_ << "\t" << #var2_"=" << var2_ << std::endl
#define flut_logvar3( var1_, var2_, var3_ ) std::cout << #var1_"=" << var1_ << "\t" << #var2_"=" << var2_ << "\t" << #var3_"=" << var3_ << std::endl
#define flut_logvar4( var1_, var2_, var3_, var4_ ) std::cout << #var1_"=" << var1_ << "\t" << #var2_"=" << var2_ << "\t" << #var3_"=" << var3_ << "\t" << #var4_"=" << var4_ << std::endl

namespace fluc
{
	namespace log
	{
		struct stream_ignore_wrapper {
			template< typename T >
			stream_ignore_wrapper& operator<<( T& value ) const { return *this; }
		};

		struct stream_output_wrapper {
			template< typename T >
			stream_output_wrapper& operator<<( T& value ) const { std::cout << T; return *this; }
		};

		const stream_ignore_wrapper ignore_stream;
		const stream_output_wrapper output_stream;
	}
}

namespace fluc
{
	namespace log
	{
#if ( FLUC_LOG_LEVEL <= FLUC_LOG_TRACE_LEVEL )
		const auto& trace = output_stream;
#else
		const auto& trace = ignore_stream;
#endif
	}
}
