#pragma once

#include "types.hpp"
#include <sstream>
#include <vector>
#include <stdarg.h>
#include <algorithm>

namespace flut
{
	/// get left n characters
	string left_str( const string& str, int i )
	{ if ( i >= 0 ) return str.substr( 0, size_t( i ) ); else return str.substr( 0, size_t( std::max( 0, int(str.size()) + i ) ) ); }

	/// get middle n characters, starting from pos
	string mid_str( const string& str, index_t pos, size_t n = string::npos ) { return str.substr( pos, n ); }

	/// get middle n characters, starting from pos
	string right_str( const string& str, int i )
	{ if ( i >= 0 ) return str.substr( str.size() - i, string::npos ); else return str.substr( size_t( -i ), string::npos ); }

	/// get middle n characters, starting from pos
	index_t in_str( const string& str, const string& substr, index_t p = 0 ) { return str.find( substr, p ); }

	/// split a string into a vector of strings
	std::vector< string > split_str( const std::string& s, const std::string& sep_chars ) {
		std::vector< std::string > strings;
		size_t ofs = s.find_first_not_of( sep_chars.c_str(), 0 );
		while ( ofs != std::string::npos ) {
			size_t ofsend = s.find_first_of( sep_chars.c_str(), ofs );
			strings.push_back( s.substr( ofs, ofsend - ofs ) );
			ofs = s.find_first_not_of( sep_chars.c_str(), ofsend );
		}
		return strings;
	}

	/// get formatted string (printf style)
	string stringf( const char* format, ... ) {
		va_list args;
		va_start( args, format );
		char buf[ 256 ];
		vsprintf_s( buf, sizeof( buf ), format, args );
		va_end( args );
		return std::string( buf );
	}

	/// Get file extension (without dot)
	string get_filename_ext( const string& str ) {
		size_t n = str.find_last_of( '.' );
		if ( n != std::string::npos ) {
			std::string ext = str.substr( n + 1 );
			if ( ext.find_last_of( "/\\" ) != std::string::npos ) // check if not part of folder
				return ext;
		}
		return std::string(); // no extension found
	}

	/// Get file without extension (without dot)
	string get_filename_stem( const string& str )
	{ return str.substr( 0, str.size() - get_filename_ext( str ).size() ); }

	/// convert any streamable type to string
	template< typename T >
	string make_str( const T& value ) { std::ostringstream str; str << value; return str.str(); }

	/// convert string to any streamable type
	template< typename T >
	T from_string( const std::string& s ) { T value; std::istringstream ostr( s ); str << value; return str.str(); }
	template<> string from_string< std::string >( const std::string& s ) { return s; }

	/// get a string between quotes
	inline string quoted( const std::string& s ) { return '\"' + s + '\"'; }
}
