#pragma once

#include <iosfwd>
#include <stdarg.h>
#include <string>
#include <vector>

namespace moper
{
	/// Get formatted string (printf style)
	std::string stringf( const char* format, ... ) {
		va_list args;
		va_start( args, format );
		char buf[ 256 ];
		vsprintf_s( buf, sizeof( buf ), format, args );
		va_end( args );
		return std::string( buf );
	}

	/// Get file extension (without dot -- or is it??)
	std::string get_filename_ext( const std::string& str ) {
		size_t n = str.find_last_of( "." );
		if ( n == std::string::npos ) {
			std::string ext = str.substr( n );
			if ( ext.find_last_of( "/\\" ) != std::string::npos ) // check if not part of folder
				return ext;
		}
		return std::string(); // no extension found
	}

	/// Get file without extension (without dot)
	std::string get_filename_stem( const std::string& str ) {
		return str.substr( 0, str.size() - get_filename_ext( str ).size() );
	}

	/// convert any streamable type to string
	template< typename T >
	string to_string( const T& value ) { std::ostringstream str; str << value; return str.str(); }

	/// convert string to any streamable type
	template< typename T >
	T from_string( const std::string& s ) { T value; std::istringstream ostr( s ); str << value; return str.str(); }
	template<> std::string from_string< std::string >( const std::string& s ) { return s; }

	/// get a string between quotes
	inline std::string quoted( const std::string& s ) { return '\"' + s + '\"'; }

	/// tokenize a string
	std::vector< std::string > split_string( const std::string& s, const std::string& sep_chars ) {
		std::vector< std::string > strings;
		size_t ofs = s.find_first_not_of( sep_chars.c_str(), 0 );
		while ( ofs != std::string::npos ) {
			size_t ofsend = s.find_first_of( sep_chars.c_str(), ofs );
			strings.push_back( s.substr( ofs, ofsend - ofs ) );
			ofs = s.find_first_not_of( sep_chars.c_str(), ofsend );
		}
		return strings;
	}
}
