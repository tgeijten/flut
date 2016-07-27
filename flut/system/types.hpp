#pragma once

#include "flut/system/build_config.hpp"

#include <string>
#include <vector>

namespace flut
{
	typedef double real_t;
	typedef real_t seconds_t;

	typedef size_t index_t;
	const size_t no_size = ~size_t( 0 );
	const index_t no_index = index_t( std::string::npos );

	using string = std::string;
	template< typename T >
	using vector = std::vector< T >;
}
