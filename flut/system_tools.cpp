#include "system_tools.hpp"
#include "string_tools.hpp"

#ifdef FLUT_COMP_MSVC
#	include <conio.h>
#	include <shlobj.h>
#endif

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

	string get_config_folder()
	{
#ifdef FLUT_COMP_MSVC
			// get the string, convert to single byte string, then free the original string (ugh)
			wchar_t* wcsLocalAppData = 0;
			SHGetKnownFolderPath( FOLDERID_LocalAppData, 0, NULL, &wcsLocalAppData );
			char mbsLocalAppData[MAX_PATH];
			size_t dummy;
			wcstombs_s( &dummy, mbsLocalAppData, MAX_PATH, wcsLocalAppData, MAX_PATH );
			CoTaskMemFree( static_cast<void*>( wcsLocalAppData ) );

			return string( mbsLocalAppData );
#else
			string homeDir = std::getenv( "HOME" );
			return homeDir + "/.config";
#endif
	}

	string FLUT_API get_application_folder()
	{
#ifdef FLUT_COMP_MSVC
		char buf[ 1024 ];
		GetModuleFileName( 0, buf, sizeof( buf ) );
		return get_filename_folder( string( buf ) );
#else
        return "";
#endif
	}

}
