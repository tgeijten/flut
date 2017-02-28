#include "system_tools.hpp"
#include "string_tools.hpp"

#ifdef FLUT_COMP_MSVC
#	include <conio.h>
#	include <shlobj.h>
#	pragma warning( disable: 4996 )
#endif

#include <fstream>
#include "system/log.hpp"
#include <chrono>
#include <corecrt_io.h>
#include <direct.h>
#include <thread>

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

	FLUT_API bool file_exists( const path& file )
	{
		std::ifstream ifs( file.str() );
		return ifs.good();
	}


	FLUT_API bool folder_exists( const path& folder )
	{
#ifdef FLUT_COMP_MSVC
		DWORD dwAttrib = GetFileAttributes( path( folder ).make_preferred().c_str() );
		return ( dwAttrib != INVALID_FILE_ATTRIBUTES && ( dwAttrib & FILE_ATTRIBUTE_DIRECTORY ) );
#else
		if ( !folder.empty() )
		{
			if ( access( folder.c_str(), 0 ) == 0 )
			{
				struct stat status;
				stat( folder.c_str(), &status );
				if ( status.st_mode & S_IFDIR )
					return true;
			}
		}
		return false; // if any condition fails
#endif
	}

	FLUT_API bool create_folder( const path& folder )
	{
#ifdef FLUT_COMP_MSVC
		return CreateDirectory( folder.c_str(), NULL ) != 0;
#else
		return mkdir( folder.c_str() ) == 0;
#endif
	}

	FLUT_API string get_date_time_str( const char* format )
	{
		// GCC did not implement std::put_time until GCC 5
#if defined(__GNUC__) && (__GNUC__ < 5)
		auto in_time_t = std::chrono::system_clock::to_time_t( std::chrono::system_clock::now() );
		char arr[100];
		std::strftime( arr, sizeof( arr ), format, std::localtime( &in_time_t ) );
		return string( arr );
#else
		auto in_time_t = std::chrono::system_clock::to_time_t( std::chrono::system_clock::now() );
		std::stringstream ss;
		ss << std::put_time( std::localtime( &in_time_t ), format );
		return ss.str();
#endif

	}

	FLUT_API void crash( const string& message )
	{
		if ( !message.empty() )
			log::critical( message );

		// crash!
		*(int*)(0) = 123;
	}

	FLUT_API void sleep( int ms )
	{
		std::this_thread::sleep_for( std::chrono::milliseconds( ms ) );
	}

	FLUT_API void set_thread_priority( thread_priority p )
	{
#ifdef FLUT_COMP_MSVC

		::SetThreadPriority( ::GetCurrentThread(), (int)p );
#elif __APPLE__
		// TODO setschedprio unavailable; maybe use getschedparam?
#else
		pthread_setschedparam( pthread_self(), SCHED_RR, (int)p + 2 );
#endif
	}
}
