#pragma once

#include "flut/system/types.hpp"
#include "flut/system/assert.hpp"

#include <sstream>
#include <stdarg.h>
#include <algorithm>

#ifdef WIN32
#	define NOMINMAX
#	define WIN32_LEAN_AND_MEAN
#	include <shlwapi.h> // used by glob_match
#	undef small // windows defines small :-S
#	pragma comment( lib, "shlwapi.lib" )
#else
#	include <fnmatch.h>
#endif

namespace flut
{
	/// get left n characters
	/// when n < 0: get string WITHOUT the left n characters
	inline string left_str( const string& str, int n )
	{ if ( n >= 0 ) return str.substr( 0, size_t( n ) ); else return str.substr( 0, size_t( std::max( 0, int(str.size()) + n ) ) ); }

	/// get middle n characters, starting from pos
	inline string mid_str( const string& str, index_t pos, size_t n = string::npos ) { return str.substr( pos, n ); }

	/// get right n characters
	/// when n < 0: get string WITHOUT the right n characters
	inline string right_str( const string& str, int n )
	{ if ( n >= 0 ) return str.substr( str.size() - n, string::npos ); else return str.substr( size_t( -n ), string::npos ); }

	/// get index of a substring in a string
	inline index_t in_str( const string& str, const string& substr, index_t p = 0 ) { return str.find( substr, p ); }

	/// split a string into a vector of strings
	inline std::vector< string > split_str( const string& s, const string& sep_chars ) {
		std::vector< string > strings;
		size_t ofs = s.find_first_not_of( sep_chars.c_str(), 0 );
		while ( ofs != string::npos ) {
			size_t ofsend = s.find_first_of( sep_chars.c_str(), ofs );
			strings.push_back( s.substr( ofs, ofsend - ofs ) );
			ofs = s.find_first_not_of( sep_chars.c_str(), ofsend );
		}
		return strings;
	}

	/// get formatted string (printf style)
	inline string stringf( const char* format, ... ) {
		va_list args;
		va_start( args, format );
		char buf[ 256 ];
		vsnprintf( buf, sizeof( buf ), format, args );
		va_end( args );
		return string( buf );
	}

	/// Get filename extension (without dot)
	inline string get_filename_ext( const string& str ) {
		size_t n = str.find_last_of( '.' );
		if ( n != string::npos ) {
			string ext = str.substr( n + 1 );
			if ( ext.find_last_of( "/\\" ) != string::npos ) // check if not part of folder
				return ext;
		}
		return string(); // no extension found
	}

	/// Get filename without extension (without dot)
	inline string get_filename_without_ext( const string& str ) {
		auto ext_len = get_filename_ext( str ).size();
		if ( ext_len > 0 ) ++ext_len; // add dot
		return str.substr( 0, str.size() - ext_len );
	}

	/// Get folder of filename (including slash, if any)
	inline string get_filename_folder( const string& str ) {
		size_t n = str.find_last_of( "/\\" );
		if ( n != string::npos ) return str.substr( 0, n + 1 );
		else return str;
	}

	/// Get filename without folder
	inline string get_filename_without_folder( const string& str ) {
		size_t n = str.find_last_of( "/\\" );
		if ( n != string::npos ) return str.substr( n + 1, string::npos );
		else return str;
	}

	/// match pattern (glob, i.e. name* or name?), uses multiple patterns delimeted by ';'
	inline bool matches_pattern( const string& str, const string& pattern, bool use_multiple_patterns = false ) {
#ifdef WIN32
		return PathMatchSpecEx( str.c_str(), pattern.c_str(), use_multiple_patterns ? PMSF_MULTIPLE : PMSF_NORMAL ) == S_OK;
#else
		std::vector<std::string> patterns = split_str( pattern, ";" );
		for ( auto p : patterns ) {
			if ( fnmatch( p.c_str(), str.c_str(), FNM_NOESCAPE ) == 0 )
				return true;
		}
		return false;
#endif
	}

	/// convert any streamable type to string
	template< typename T > string to_str( const T& value ) { std::ostringstream str; str << value; return str.str(); }
	template<> inline string to_str < string >( const string& s ) { return s; }

	/// convert string to any streamable type
	template< typename T > T from_str( const string& s ) { T value; std::stringstream str( s ); str >> value; return value; }
	template<> inline string from_str< string >( const string& s ) { return s; }

	/// get a string between quotes
	inline string quoted( const string& s ) { return '\"' + s + '\"'; }
}
