#include "log.hpp"
#include "assert.hpp"

namespace flut
{
	namespace log
	{
		level dynamic_log_level = level::info_level;

		void set_level( level l )
		{
			flut_assert( l >= FLUT_LOG_LEVEL_ALL && l <= FLUT_LOG_LEVEL_NONE );
			dynamic_log_level = l;
		}

		FLUT_API void set_level( int l )
		{
			set_level( static_cast<level>( l ) );
		}

		level get_level()
		{
			return dynamic_log_level;
		}
	}
}
