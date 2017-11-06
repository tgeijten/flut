#pragma once

#include "flut/system/platform.hpp"
#include "flut/system/path.hpp"
#include "flut/system/error_code.hpp"

namespace flut
{
	FLUT_API char wait_for_key();
	FLUT_API string get_date_time_str( const char* format = "%Y-%m-%d_%H.%M.%S" );
	FLUT_API void crash( const string& message = "" );
	FLUT_API void sleep( int milliseconds );
	FLUT_API string tidy_identifier( const string& id );
	FLUT_API string clean_type_name( const char* name );
	template< typename T > string clean_type_name() { return clean_type_name( typeid( T ).name() ); }
	enum class thread_priority { lowest = -2, low = -1, normal = 0, high = 1, highest = 2 };
	FLUT_API void set_thread_priority( thread_priority p );
}
