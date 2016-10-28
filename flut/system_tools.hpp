#pragma once

#include "flut/system/platform.hpp"
#include "flut/system/path.hpp"

namespace flut
{
	char FLUT_API wait_for_key();
	path FLUT_API get_config_folder();
	path FLUT_API get_documents_folder();
	path FLUT_API get_application_folder();
}
