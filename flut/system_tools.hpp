#pragma once

#include "flut/system/platform.hpp"
#include "flut/system/path.hpp"

namespace flut
{
	FLUT_API char wait_for_key();
	FLUT_API path get_config_folder();
	FLUT_API path get_documents_folder();
	FLUT_API path get_application_folder();
	FLUT_API bool exists( const path& file );
	FLUT_API string get_date_time_str();
}
