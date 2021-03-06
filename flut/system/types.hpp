#pragma once

#include "flut/system/build_config.hpp"

#include <string>
#include <vector>
#include <memory>
#include <utility>

namespace flut
{
	typedef double real_t;
	typedef real_t seconds_t;
	typedef long long nanoseconds_t;

	typedef size_t index_t;
	const size_t no_size = ~size_t( 0 );
	const index_t no_index = index_t( std::string::npos );

	using std::string;
	using std::pair;
	using std::vector;
	template< typename T > using u_ptr = std::unique_ptr< T >;
	template< typename T > using s_ptr = std::shared_ptr< T >;
}
