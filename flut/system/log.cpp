#include "assert.hpp"
#include "log.hpp"
#include "log_sink.hpp"

namespace flut
{
	namespace log
	{
		void std_cout_log( level l, const std::string& msg ) { std::cout << msg << std::endl; }
		level lowest_log_level = level::never_log_level;
		std::vector< sink* > global_sinks;

		void log_output( level l, std::stringstream& msg )
		{
			for ( auto s : global_sinks )
				s->try_send_log_message( l, msg.str() );
		}

		void add_sink( sink* s )
		{
			flut_assert( s != nullptr );
			if ( std::find( global_sinks.begin(), global_sinks.end(), s ) == global_sinks.end() )
			{
				global_sinks.push_back( s );
				update_lowest_log_level();
			}
		}

		void remove_sink( sink* s )
		{
			auto it = std::find( global_sinks.begin(), global_sinks.end(), s );
			if ( it != global_sinks.end() ) global_sinks.erase( it );
			update_lowest_log_level();
		}

		void update_lowest_log_level()
		{
			lowest_log_level = critical_level;
			for ( auto s : global_sinks )
				if ( s->get_log_level() < lowest_log_level ) lowest_log_level = s->get_log_level();
		}

		bool test_log_level( level l )
		{
			return l >= lowest_log_level;
		}
	}
}
