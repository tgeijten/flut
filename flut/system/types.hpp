#pragma once

#include "flut/system/build_config.hpp"

#include <string>
#include <vector>

namespace flut
{
	typedef double real_t;

	typedef size_t index_t;
	const index_t no_index = index_t( std::string::npos );

	using string = std::string;
	template< typename T >
	using vector = std::vector< T >;
}
