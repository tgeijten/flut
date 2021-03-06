#pragma once

#include "system/platform.hpp"
#include "system/types.hpp"
#include "system/assert.hpp"
#include "system/error_code.hpp"
#include "system/path.hpp"
#include "flag_set.hpp"

#ifdef FLUT_COMP_MSVC
#	pragma warning( push )
#	pragma warning( disable: 4251 )
#endif

namespace flut
{
	inline const char* default_delimiters() { return " \t\r\n\f\v"; }

	/// blazing-fast class for reading text stream-style
	class FLUT_API char_stream
	{
	public:
		/// construct char_stream using given zero terminated char buffer
		char_stream( const char* buf, const char* delim = default_delimiters() );

		/// construct char_stream from rvalue string
		char_stream( string&& other, const char* delim = default_delimiters() );

		/// construct char_stream with contents read from file
		char_stream( const path& filename, const char* delim = default_delimiters() );

		~char_stream() {}

		char_stream& operator>>( float& v ) { v = strtof( cur_pos, &cur_pos_end ); process_end_pos(); return *this; }
		char_stream& operator>>( double& v ) { v = strtod( cur_pos, &cur_pos_end ); process_end_pos(); return *this; }
		char_stream& operator>>( long& v ) { v = strtol( cur_pos, &cur_pos_end, radix ); process_end_pos(); return *this; }
		char_stream& operator>>( long long& v ) { v = strtoll( cur_pos, &cur_pos_end, radix ); process_end_pos(); return *this; }
		char_stream& operator>>( unsigned long& v ) { v = strtoul( cur_pos, &cur_pos_end, radix ); process_end_pos(); return *this; }
		char_stream& operator>>( unsigned long long& v ) { v = strtoull( cur_pos, &cur_pos_end, radix ); process_end_pos(); return *this; }
		char_stream& operator>>( string& s );

		char_stream& operator>>( int& v ) { v = (int)strtol( cur_pos, &cur_pos_end, radix ); process_end_pos(); return *this; }
		char_stream& operator>>( unsigned int& v ) { v = (unsigned int)strtoul( cur_pos, &cur_pos_end, radix ); process_end_pos(); return *this; }
		char_stream& operator>>( short& v ) { v = (short)strtol( cur_pos, &cur_pos_end, radix ); process_end_pos(); return *this; }
		char_stream& operator>>( unsigned short& v ) { v = (unsigned short)strtoul( cur_pos, &cur_pos_end, radix ); process_end_pos(); return *this; }

		string get_line();
		string get_token( const char* operators = "", const char* quotations = "\"" );
		char getc() { char c = *cur_pos++; test_eof(); return c; }
		char peekc() { return *cur_pos; }

		bool good() { return !buffer_flags.any(); }
		bool eof() { return buffer_flags.get< eof_flag >(); }
		bool fail() { return buffer_flags.get< fail_flag >(); }

	private:
		void init_buffer( const char* b, size_t len );

		void skip_delimiters() { while ( !test_eof() && strchr( delimiters_, *cur_pos ) ) ++cur_pos; }
		void skip_delimiters( const char* delim ) { while ( !test_eof() && strchr( delim, *cur_pos ) ) ++cur_pos; }
		bool test_eof() { if ( cur_pos == buffer_end ) { buffer_flags.set< eof_flag >(); return true; } else return false; }
		void process_end_pos() { if ( cur_pos == cur_pos_end ) buffer_flags.set< fail_flag >(); else { cur_pos = cur_pos_end; skip_delimiters(); } }

		int radix = 10;
		string str_buffer;
		const char* buffer;
		const char* cur_pos;
		char* cur_pos_end;
		const char* buffer_end;
		const char* delimiters_;

		enum buffer_flag { fail_flag, eof_flag };
		flag_set< buffer_flag > buffer_flags;
	};

	/// load file into char buffer
	FLUT_API char_stream load_char_stream( const path& filename, const char* delimiters = default_delimiters(), error_code* ec = nullptr );
}

#ifdef FLUT_COMP_MSVC
#	pragma warning( pop )
#endif
