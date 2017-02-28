#pragma once

#include "system/platform.hpp"
#include "system/types.hpp"
#include "system/assert.hpp"
#include "flag_set.hpp"

#ifdef FLUT_COMP_MSVC
#	pragma warning( push )
#	pragma warning( disable: 4251 )
#endif

namespace flut
{
	/// blazing-fast class for reading text stream-style
	class FLUT_API char_stream
	{
	public:
		/// construct empty char_stream
		char_stream();

		/// construct char_stream using given zero terminated char buffer
		char_stream( const char* buf );

		/// construct char_stream from rvalue string
		char_stream( string&& other );
		~char_stream() {}

		char_stream& operator>>( float& v ) { v = strtof( cur_pos, &end_pos ); process_end_pos(); return *this; }
		char_stream& operator>>( double& v ) { v = strtod( cur_pos, &end_pos ); process_end_pos(); return *this; }
		char_stream& operator>>( long& v ) { v = strtol( cur_pos, &end_pos, radix ); process_end_pos(); return *this; }
		char_stream& operator>>( long long& v ) { v = strtoll( cur_pos, &end_pos, radix ); process_end_pos(); return *this; }
		char_stream& operator>>( unsigned long& v ) { v = strtoul( cur_pos, &end_pos, radix ); process_end_pos(); return *this; }
		char_stream& operator>>( unsigned long long& v ) { v = strtoull( cur_pos, &end_pos, radix ); process_end_pos(); return *this; }
		char_stream& operator>>( string& s );

		char_stream& operator>>( int& v ) { v = (int)strtol( cur_pos, &end_pos, radix ); process_end_pos(); return *this; }
		char_stream& operator>>( unsigned int& v ) { v = (unsigned int)strtoul( cur_pos, &end_pos, radix ); process_end_pos(); return *this; }
		char_stream& operator>>( short& v ) { v = (short)strtol( cur_pos, &end_pos, radix ); process_end_pos(); return *this; }
		char_stream& operator>>( unsigned short& v ) { v = (unsigned short)strtoul( cur_pos, &end_pos, radix ); process_end_pos(); return *this; }

		string get_line();
		string get_token( const char* operators = "" );
		char getc() { char c = *cur_pos; if ( c == '\0' ) buffer_flags.set< eof_flag >(); else ++cur_pos; return c; }
		char peekc() { if ( cur_pos == '\0' ) buffer_flags.set< eof_flag >(); return *cur_pos; }

		bool good() { return !buffer_flags.any(); }
		bool eof() { return buffer_flags.get< eof_flag >(); }
		bool fail() { return buffer_flags.get< fail_flag >(); }

	private:
		void init_buffer( const char* b, size_t len );

		void skip_whitespace()
		{ for( ; isspace( *cur_pos ); ++cur_pos ); if ( *cur_pos == '\0' ) buffer_flags.set< eof_flag >(); }

		void process_end_pos()
		{ if ( cur_pos == end_pos ) buffer_flags.set< fail_flag >(); cur_pos = end_pos; skip_whitespace(); }

		int radix = 10;
		string str_buffer;
		const char* buffer;
		const char* cur_pos;
		char* end_pos;
		const char* buffer_end;

		enum buffer_flag { fail_flag, eof_flag };
		flag_set< buffer_flag > buffer_flags;
	};

	/// load file into char buffer
	FLUT_API char_stream load_char_stream( const string& filename );
}

#ifdef FLUT_COMP_MSVC
#	pragma warning( pop )
#endif
