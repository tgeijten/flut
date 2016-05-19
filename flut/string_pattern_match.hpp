#pragma once

#include "flut/system/types.hpp"
#include "flut/system/assert.hpp"
#include "flut/string_tools.hpp"

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
	/// match pattern (glob, i.e. name* or name?), can use multiple delimited patterns, default delimiter = ';'
	inline bool matches_pattern( const string& str, const string& pattern, const char* pattern_delim_chars = ";" ) {
		std::vector<std::string> patterns = split_str( pattern, pattern_delim_chars );
		for ( auto p : patterns ) {
#ifdef WIN32
			if ( PathMatchSpecEx( str.c_str(), p.c_str(), PMSF_NORMAL ) == S_OK )
				return true;
#else
			if ( fnmatch( p.c_str(), str.c_str(), FNM_NOESCAPE ) == 0 )
				return true;
#endif
		}
		return false;
	}
}
