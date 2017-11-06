#include "flut_version.hpp"

namespace flut
{
	version g_version = version( 0, 1, 0 );
	version get_flut_version() { return g_version; }
}
