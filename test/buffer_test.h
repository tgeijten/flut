#pragma once

#include <vector>
#include "flut/math/vec3.hpp"
#include "flut/system/log.hpp"
#include "flut/storage/interpolation.hpp"
#include "flut/storage/buffer_channel_info.hpp"

namespace flut
{
	void buffer_test()
	{
		// more tests
		std::vector< std::pair< double, vec3 > > buf_test;
		buf_test.push_back( std::make_pair( 0, vec3( 1, 0, 0 ) ) );
		buf_test.push_back( std::make_pair( 1, vec3( 0, 1, 0 ) ) );
		buf_test.push_back( std::make_pair( 3, vec3( 0, 1, 2 ) ) );
		for ( int d = -10; d < 40; ++d )
			log::trace( 0.1 * d, ": ", interpolated_value( buf_test, 0.1 * d ) );

		// more tests
		std::vector< vec3 > buf_test2;
		buf_test2.push_back( vec3( 1, 0, 0 ) );
		buf_test2.push_back( vec3( 0, 1, 0 ) );
		buf_test2.push_back( vec3( 0, 1, 2 ) );
		for ( int d = -10; d < 40; ++d )
			log::trace( 0.1 * d, ": ", interpolated_value( buf_test2, 0.1 * d ) );

		buffer_channel_info< string > bci1;
		buffer_channel_info< void > bci2;

		bci1.add_channel( "test" );
		bci2.add_channel();

		flut_logvar2( sizeof(bci1), sizeof(bci2) );
		
	}
}