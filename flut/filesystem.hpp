#pragma once

#include "system/path.hpp"
#include "system/error_code.hpp"

namespace flut
{
	FLUT_API path get_config_folder();
	FLUT_API path get_documents_folder();
	FLUT_API path get_application_folder();
	FLUT_API bool remove( const path& file );
	FLUT_API bool file_exists( const path& file );
	FLUT_API bool folder_exists( const path& folder );
	FLUT_API bool create_folder( const path& folder );
	FLUT_API path create_unique_folder( const path& folder, int max_attempts = 9999 );
	FLUT_API string load_string( const path& filename, error_code* ec = nullptr );
	FLUT_API void current_path( const path& p );
	FLUT_API path current_path();
}
