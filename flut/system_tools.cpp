#include "system_tools.hpp"
#include "string_tools.hpp"

#ifdef FLUT_COMP_MSVC
#	include <conio.h>
#	include <shlobj.h>
#endif

#include <fstream>

namespace flut
{
	char wait_for_key()
	{
#ifdef FLUT_COMP_MSVC
			return _getch();
#else
			return 0;
#endif
	}

#ifdef FLUT_COMP_MSVC
	// define this helper function for windows, since it's so complicated
	string get_known_windows_folder( KNOWNFOLDERID id )
	{
		// get the string, convert to single byte string, then free the original string (ugh)
		wchar_t* wcsLocalAppData = 0;
		SHGetKnownFolderPath( id, 0, NULL, &wcsLocalAppData );
		char mbsLocalAppData[MAX_PATH];
		wcstombs_s( size_t(), mbsLocalAppData, MAX_PATH, wcsLocalAppData, MAX_PATH );
		CoTaskMemFree( static_cast<void*>( wcsLocalAppData ) );
		return string( mbsLocalAppData );
	}
#endif

	path get_config_folder()
	{
#ifdef FLUT_COMP_MSVC
		return get_known_windows_folder( FOLDERID_LocalAppData );
#else
		string homeDir = std::getenv( "HOME" );
		return homeDir + "/.config";
#endif
	}

	path get_documents_folder()
	{
#ifdef FLUT_COMP_MSVC
		return get_known_windows_folder( FOLDERID_Documents );
#else
		return std::getenv( "HOME" );
#endif
	}

	path get_application_folder()
	{
#ifdef FLUT_COMP_MSVC
		char buf[ 1024 ];
		GetModuleFileName( 0, buf, sizeof( buf ) );
		return get_filename_folder( string( buf ) );
#else
		return "";
#endif
	}

	FLUT_API bool exists( const path& file )
	{
		std::ifstream ifs( file.str() );
		return ifs.good();
	}
}
