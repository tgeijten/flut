#pragma once

#include <string>
#include <vector>
#include <memory>

namespace flut
{
	typedef double real_t;

	typedef size_t index_t;
	const index_t no_index = index_t( -1 );

	using string = std::string;
	//template< typename T > using vector< T > = std::vector< T >;
	//template< typename T > using uptr< T > = std::unique_ptr< T >;
}
