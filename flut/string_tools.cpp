#include "string_tools.hpp"

#ifdef FLUT_COMP_MSVC
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
	vector< string > split_str( const string& s, const string& sep_chars )
	{
		std::vector< string > strings;
		size_t ofs = s.find_first_not_of( sep_chars.c_str(), 0 );
		while ( ofs != string::npos ) {
			size_t ofsend = s.find_first_of( sep_chars.c_str(), ofs );
			strings.push_back( s.substr( ofs, ofsend - ofs ) );
			ofs = s.find_first_not_of( sep_chars.c_str(), ofsend );
		}
		return strings;
	}

	string stringf( const char* format, ... )
	{
#ifdef FLUT_COMP_MSVC
#	pragma warning( push )
#	pragma warning( disable: 4996 )
#endif
		va_list args;
		va_start( args, format );
		char buf[256];
		vsnprintf( buf, sizeof( buf ), format, args );
		va_end( args );
		return string( buf );
#ifdef FLUT_COMP_MSVC
#	pragma warning( pop )
#endif
	}

	bool matches_pattern( const string& str, const string& pattern, const char* pattern_delim_chars )
	{
		std::vector<std::string> patterns = split_str( pattern, pattern_delim_chars );
		for ( auto p : patterns ) {
#ifdef FLUT_COMP_MSVC
			flut_assert_msg( strcmp( pattern_delim_chars, ";" ), "Pattern delimiter must be ';' for MSVC" );
			if ( PathMatchSpecEx( str.c_str(), p.c_str(), PMSF_NORMAL ) == S_OK )
				return true;
#else
			if ( fnmatch( p.c_str(), str.c_str(), FNM_NOESCAPE ) == 0 )
				return true;
#endif
		}
		return false;
	}

	flut::string get_filename_ext( const string& str )
	{
		size_t n = str.find_last_of( '.' );
		if ( n != string::npos ) {
			string ext = str.substr( n + 1 );
			if ( ext.find_last_of( "/\\" ) != string::npos ) // check if not part of folder
				return ext;
		}
		return string(); // no extension found
	}

	flut::string get_filename_without_ext( const string& str )
	{
		auto ext_len = get_filename_ext( str ).size();
		if ( ext_len > 0 ) ++ext_len; // add dot
		return str.substr( 0, str.size() - ext_len );
	}

	flut::string get_filename_folder( const string& str )
	{
		size_t n = str.find_last_of( "/\\" );
		if ( n != string::npos ) return str.substr( 0, n + 1 );
		else return str;
	}

	flut::string get_filename_without_folder( const string& str )
	{
		size_t n = str.find_last_of( "/\\" );
		if ( n != string::npos ) return str.substr( n + 1, string::npos );
		else return str;
	}

}