#pragma once

#include "flut/system/platform.hpp"
#include "flut/system/types.hpp"
#include "flut/system/assert.hpp"
#include "system/path.hpp"
#include "char_stream.hpp"

#include <iomanip>
#include <sstream>
#include <algorithm>
#include <stdlib.h>

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

	/// remove leading and trailing spaces
	FLUT_API string trim_str( const string& str );

	/// split a string into a vector of strings
	FLUT_API vector< string > split_str( const string& s, const string& sep_chars );

	/// split string into trimmed key / value pair
	FLUT_API std::pair< string, string > to_key_value( const string& s, const string& sep_char = "=" );

	inline bool scan_str_impl( std::stringstream& str ) { return true; }
	template< typename T, typename... Args > bool scan_str_impl( std::stringstream& str, T& v, Args&... args )
	{ str >> v; if ( str.good() ) return scan_str_impl( str, args... ); else return false; }

	/// read variables from string
	template< typename... Args > bool scan_str( const string& s, Args&... args )
	{ std::stringstream str( s ); return scan_str_impl( str, args... ); }

	/// get formatted string (printf style)
	FLUT_API string stringf( const char* format, ... );

	/// match pattern (glob, i.e. name* or name?), can use multiple delimited patterns, default delimiter = ';'
	FLUT_API bool matches_pattern( const string& str, const string& pattern, const char* pattern_delim_chars = ";" );

	/// set precision used in to_str calls, returns previous precision
	FLUT_API int set_to_str_precision( int p );
	FLUT_API int to_str_precision();

	/// convert any streamable type to string
	template< typename T > string to_str( const T& value ) { return string_cast< T >::to( value ); }

	/// convert string to any streamable type
	template< typename T > T from_str( const string& s ) { return string_cast< T >::from( s ); }

	/// convert space-delimited string to vector of elements
	template< typename T > vector< T > from_vec_str( const string& s, size_t size ) {
		char_stream str( s.c_str() );
		vector< T > vec; if ( size != no_index ) vec.reserve( size );
		while ( str.good() ) { T elem; str >> elem; if ( !str.fail() ) vec.push_back( elem ); }
		return vec;
	}

	/// make string with contents of a file
	FLUT_API string load_string( const path& filename );

	/// get a string between quotes
	inline string quoted( const string& s ) { return '\"' + s + '\"'; }

	/// Get filename extension (without dot)
	FLUT_API string get_filename_ext( const string& str );

	/// Get filename without extension (without dot)
	FLUT_API string get_filename_without_ext( const string& str );

	/// Get folder of filename (including slash, if any)
	FLUT_API string get_filename_folder( const string& str );

	/// Get filename without folder
	FLUT_API string get_filename_without_folder( const string& str );
}
