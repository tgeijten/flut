#include "flut_test_config.h"
#include "flut/system/log.hpp"

int log_level = FLUT_STATIC_LOG_LEVEL;

int get_dynamic_log_level()
{
	return log_level;
}

void set_dynamic_log_level( int l )
{
	log_level = l;
}
