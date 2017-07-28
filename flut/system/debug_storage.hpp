#pragma once

#include "platform.hpp"
#include "path.hpp"

namespace flut
{
	void FLUT_API set_debug_output( const path& filename );
	void FLUT_API write_debug( const string& label, float data );
}
