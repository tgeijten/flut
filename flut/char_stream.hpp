#pragma once

#include "system/platform.hpp"
#include "system/types.hpp"
#include "system/assert.hpp"
#include "flags.hpp"

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
		char_stream();
		char_stream( const char* buf );
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

		bool good() { return !flags.any(); }
		bool eof() { return flags.get< eof_flag >(); }
		bool fail() { return flags.get< fail_flag >(); }

	private:
		void init_buffer( const char* b );

		void skip_whitespace()
		{ for( ; isspace( *cur_pos ); ++cur_pos ); if ( *cur_pos == '\0' ) flags.set< eof_flag >(); }

		void process_end_pos()
		{ if ( cur_pos == end_pos ) flags.set< fail_flag >(); cur_pos = end_pos; skip_whitespace(); }

		int radix = 10;
		string str_buffer;
		const char* buffer;
		const char* cur_pos;
		char* end_pos;

		enum buffer_flag { fail_flag, eof_flag };
		flags< buffer_flag > flags;
	};

	/// load file into char buffer
	FLUT_API char_stream load_char_buffer( const string& filename );
}

#ifdef FLUT_COMP_MSVC
#	pragma warning( pop )
#endif
