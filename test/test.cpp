
#include "math_test.h"
#include "buffer_test.h"

int main( int argc, char* argv[] )
{
	log::set_dynamic_log_level( FLUT_LOG_LEVEL_INFO );

	flut_logvar2( constants<double>::epsilon(), constants<double>::relaxed_epsilon() );
	flut_logvar2( constants<float>::epsilon(), constants<float>::relaxed_epsilon() );

	math_test();
	buffer_test();

	_getch();

	return 0;
}
