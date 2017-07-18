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
#include <thread>
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>

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
			struct stat status;
			if ( stat( folder.c_str(), &status ) == 0 )
			{
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
		return mkdir( folder.c_str(), 0777 ) == 0;
#endif
	}

	FLUT_API path create_unique_folder( const path& folder, int max_attempts )
	{
		path unique_folder = folder;
		bool success = false;
		for ( int i = 0; i < max_attempts && !success; ++i )
		{
			if ( i > 0 )
				unique_folder = folder + stringf( " (%d)", i );

			if ( !folder_exists( unique_folder ) )
				success = create_folder( unique_folder ); // try to create folder
		}
		flut_error_if( !success, "Could not create unique folder after " + to_str( max_attempts ) + " attempts" );

		return unique_folder;
	}

	FLUT_API void append_string( const path& file, const string& str )
	{
		std::ofstream ofs( file.str(), std::ios::app );
		ofs << str;
	}

	FLUT_API bool remove( const path& file )
	{
		return std::remove( file.c_str() ) == 0;
	}

	FLUT_API string get_date_time_str( const char* format )
	{
		auto in_time_t = std::chrono::system_clock::to_time_t( std::chrono::system_clock::now() );
		std::stringstream ss;
		ss << std::put_time( std::localtime( &in_time_t ), format );
		return ss.str();
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

	FLUT_API string tidy_identifier( const string& id )
	{
		size_t pos = id.find_last_of( ':' );
		if ( pos != string::npos )
			return trim_str( id.substr( pos + 1 ), "_" ); // remove anything before :: plus underscores
		else if ( str_begins_with( id, "m_" ) )
			return trim_right_str( id.substr( 2 ), "_" ); // remove m_ plus underscores
		else return trim_str( id, "_" ); // remove underscores
	}

	FLUT_API string clean_type_name( const char* name )
	{
#ifdef FLUT_COMP_MSVC
		string str = name;
#else
		int status;
		char* cleanType = abi::__cxa_demangle( name, 0, 0, &status );
		std::string str = std::string( cleanType );
		free( cleanType );
#endif
		size_t pos = str.find_last_of( ": " );
		return ( pos != std::string::npos ) ? str.substr( pos + 1 ) : str;
	}

	FLUT_API string load_string( const path& filename, error_code* ec )
	{
		// this method uses a stringbuf, which may be slower but is more stable
		std::ifstream ifstr( filename.str() );
		if ( !ifstr.good() )
		{
			if ( try_set_error( ec, "Could not open " + filename.str() ) )
				return "";
			else flut_error( "Could not open " + filename.str() );
		}
		std::stringstream buf;
		buf << ifstr.rdbuf();
		return buf.str();
	}

	FLUT_API void set_thread_priority( thread_priority p )
	{
#ifdef FLUT_COMP_MSVC
		::SetThreadPriority( ::GetCurrentThread(), (int)p );
#elif __APPLE__
		// TODO setschedprio unavailable; maybe use getschedparam?
#else
		pthread_setschedprio( pthread_self(), (int)p );
#endif
	}
}
