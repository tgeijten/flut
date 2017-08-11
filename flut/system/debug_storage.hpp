#pragma once

#include "platform.hpp"
#include "path.hpp"

namespace flut
{
	FLUT_API void set_debug_output( const path& filename );
	FLUT_API void write_debug( const string& label, float data );
}
