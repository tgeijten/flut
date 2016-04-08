#pragma once

#define FLUT_STATIC_LOG_LEVEL FLUT_LOG_LEVEL_INFO
#define FLUT_DYNAMIC_LOG_LEVEL get_dynamic_log_level()

int get_dynamic_log_level();
void set_dynamic_log_level( int l );
