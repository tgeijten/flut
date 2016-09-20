#include "log.hpp"
#include "assert.hpp"

namespace flut
{
	namespace log
	{
		void std_cout_log( level l, const std::string& msg ) { std::cout << msg << std::endl; }
		level dynamic_log_level = level::info_level;
		log_output_func log_output_func_var = std_cout_log;

		void set_level( level l )
		{
			flut_assert( l >= FLUT_STATIC_LOG_LEVEL && l <= FLUT_LOG_LEVEL_NONE );
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

		FLUT_API log_output_func& get_log_output_func()
		{
			return log_output_func_var;
		}

		FLUT_API void set_log_output_func( log_output_func& f )
		{
			log_output_func_var = f;
		}

	}
}
