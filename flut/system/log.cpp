#include "log.hpp"
#include "assert.hpp"

namespace flut
{
	namespace log
	{
		int dynamic_log_level = FLUT_LOG_LEVEL_INFO;

		void set_level( int level )
		{
			flut_assert( level >= FLUT_LOG_LEVEL_ALL && level <= FLUT_LOG_LEVEL_NONE );
			dynamic_log_level = level;
		}

		int get_level()
		{
			return dynamic_log_level;
		}
	}
}
