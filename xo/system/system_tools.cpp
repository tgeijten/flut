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
