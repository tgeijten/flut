#pragma once

#include "flut/system/platform.hpp"
#include "flut/system/path.hpp"

namespace flut
{
	FLUT_API char wait_for_key();
	FLUT_API path get_config_folder();
	FLUT_API path get_documents_folder();
	FLUT_API path get_application_folder();
	FLUT_API bool file_exists( const path& file );
	FLUT_API bool folder_exists( const path& folder );
	FLUT_API bool create_folder( const path& folder );
	FLUT_API string get_date_time_str( const char* format = "%Y-%m-%d_%H.%M.%S" );
	FLUT_API void crash( const string& message = "" );
	FLUT_API void sleep( int milliseconds );

	enum class thread_priority { lowest = -2, low = -1, normal = 0, high = 1, highest = 2 };
	FLUT_API void set_thread_priority( thread_priority p );
}
