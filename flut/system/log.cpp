#include "log.hpp"

namespace flut
{
	namespace log
	{
		static int dynamic_log_level = FLUT_LOG_LEVEL;
		void set_dynamic_log_level( int level ) { dynamic_log_level = level; }
		int get_dynamic_log_level() { return dynamic_log_level; }
	}
}
