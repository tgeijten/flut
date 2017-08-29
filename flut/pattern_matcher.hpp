#pragma once

#include <vector>
#include "string_tools.hpp"

namespace flut
{
	struct pattern_matcher
	{
		pattern_matcher() {}
		pattern_matcher( const std::string& pattern, const char* delimeters = ";" ) : patterns( split_str( pattern, delimeters ) ) {}

		// returns true if pattern matches string
		bool operator()( const string& str ) const {
			for ( auto& p : patterns )
				if ( pattern_match( str, p ) ) return true;
			return false;
		}

		template< typename T > bool operator()( const T& str ) const { return operator()( static_cast< const string& >( *str ) ); }
		template< typename T > bool operator()( const T* str ) const { return operator()( static_cast< const string& >( *str ) ); }

		template< typename It > It find_match( It begin, It end ) const {
			while ( begin != end && !match( static_cast< const string& >( *begin ) ) ) ++begin;
		}

		std::vector< std::string > patterns;
	};
}
