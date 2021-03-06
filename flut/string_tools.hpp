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
	/// get left n characters, if n is negative, get string WITHOUT the left n characters
	inline string left_str( const string& str, int n )
	{ if ( n >= 0 ) return str.substr( 0, size_t( n ) ); else return str.substr( 0, size_t( std::max( 0, int(str.size()) + n ) ) ); }

	/// get middle n characters, starting from pos
	inline string mid_str( const string& str, index_t pos, size_t n = string::npos ) { return str.substr( pos, n ); }

	/// get right n characters, if n is negative, get string WITHOUT the right n characters
	inline string right_str( const string& str, int n )
	{ if ( n >= 0 ) return str.substr( str.size() - n, string::npos ); else return str.substr( size_t( -n ), string::npos ); }

	/// get index of a substring in a string
	inline index_t in_str( const string& str, const string& substr, index_t p = 0 ) { return str.find( substr, p ); }

	/// check if a string ends with a string
	inline bool str_begins_with( const string& str, const string& substr ) { return str.find( substr ) == 0; }

	/// check if a string ends with a string
	inline bool str_ends_with( const string& str, const string& substr )
	{ auto s1 = str.size(), s2 = substr.size(); return s1 >= s2 && ( str.find( substr ) == s1 - s2 ); }

	/// remove leading and trailing spaces and newlines
	FLUT_API string trim_str( const string& str, const char* trim_chars = " \t\r\n\f\v" );

	/// remove trailing spaces and newlines
	FLUT_API string trim_right_str( const string& str, const char* trim_chars = " \t\r\n\f\v" );

	/// split a string into a vector of strings
	FLUT_API vector< string > split_str( const string& s, const string& sep_chars );

	/// get the string left / right of a delimiter
	FLUT_API string left_of_str( const string& s, const string& sep_chars );
	FLUT_API string right_of_str( const string& s, const string& sep_chars );

	/// split string into trimmed key / value pair
	FLUT_API std::pair< string, string > make_key_value_str( const string& s, const string& sep_char = "=" );

	inline int scan_str_impl( char_stream& str ) { return 0; }
	template< typename T, typename... Args > int scan_str_impl( char_stream& str, T& v, Args&... args )
	{ str >> v; return str.good() ? scan_str_impl( str, args... ) + 1 : 0; }

	/// read variables from string
	template< typename... Args > int scan_str( const string& s, Args&... args )
	{ char_stream str( s.c_str() ); return scan_str_impl( str, args... ); }

	/// get formatted string (printf style)
	FLUT_API string stringf( const char* format, ... );

	/// match pattern (glob, i.e. name* or name?)
	FLUT_API bool pattern_match( const string& str, const string& pattern );

	/// set precision used in to_str calls, returns previous precision
	FLUT_API int set_to_str_precision( int p );
	FLUT_API int to_str_precision();

	/// convert any streamable type to string
	template< typename T > string to_str( const T& value ) { return string_cast< T >::to( value ); }

	/// convert string to any streamable type
	template< typename T > T from_str( const string& s ) { return string_cast< T >::from( s ); }

	/// convert space-delimited string to vector of elements
	template< typename T > vector< T > str_to_vec( const string& s, size_t max_values, const char* delim = default_delimiters() ) {
		char_stream str( s.c_str(), delim );
		vector< T > vec; if ( max_values != no_index ) vec.reserve( max_values );
		while ( str.good() && vec.size() < max_values ) { T elem; str >> elem; if ( !str.fail() ) vec.push_back( elem ); }
		return vec;
	}

	/// get a string between quotes
	FLUT_API string encode_char( char c );

	/// get a string between quotes
	FLUT_API char decode_char( const char* buf, size_t buf_size, int* len );

	/// get a string between quotes
	FLUT_API string quoted( const string& s );

	/// get a string between quotes
	FLUT_API bool needs_quotes( const string& s );

	/// get a string between quotes
	FLUT_API string try_quoted( const string& s );

	/// get a string between quotes
	FLUT_API string try_unquoted( const string& s );

	/// Get filename extension (without dot)
	FLUT_API string get_filename_ext( const string& str );

	/// Get filename without extension (without dot)
	FLUT_API string get_filename_without_ext( const string& str );

	/// Get folder of filename (including slash, if any)
	FLUT_API string get_filename_folder( const string& str );

	/// Get filename without folder
	FLUT_API string get_filename_without_folder( const string& str );
}
