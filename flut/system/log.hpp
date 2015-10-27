#pragma once

#include <iosfwd>
#include <ostream>

#define fluc_do_periodic( interval_, statement_ ) { static local_count_ = 0; if ( local_count_++ % interval_ == 0 ) { statement_; } }

#define FLUC_LOG_TRACE_LEVEL 1
#define FLUC_LOG_INFO_LEVEL 2

#ifndef FLUC_LOG_LEVEL
#define FLUC_LOG_LEVEL info_level
#endif

#ifndef FLUC_LOG_OUTPUT_STREAM
#define FLUC_LOG_OUTPUT_STREAM std::cout
#endif

namespace fluc
{
	namespace log
	{
		struct stream_ignore_wrapper {
			template< typename T >
			null_stream& operator<<( T& value ) const { return *this; }
		};

		struct stream_output_wrapper {
			template< typename T >
			null_stream& operator<<( T& value ) const { std::cout << T; return *this; }
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

