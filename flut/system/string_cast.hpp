#pragma once

#include <sstream>
#include "types.hpp"

namespace flut
{
	template< typename T, typename E = void > struct string_cast {
		static T from( const string& s ) { T value; std::stringstream str( s ); str >> value; return value; }
		static string to( const T& value ) { std::ostringstream str; str << value; return str.str(); }
	};

	template<> struct string_cast< string, void > {
		static string from( const string& s ) { return s; }
		static string to( const string& value ) { return value; }
	};

	template< typename T > struct string_cast< T, typename std::enable_if< std::is_enum< T >::value >::type > {
		static T from( const string& s ) { return static_cast< T >( string_cast< int >::from( s ) ); }
		static string to( const T& v ) { return string_cast< int >::to( static_cast< int >( v ) ); }
	};
}
