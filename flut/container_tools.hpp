#pragma once

#include "types.hpp"

namespace flut
{
	template< typename T >
	index_t find_index( const vector< T >& vec, const T& val ) {
		auto it = std::find( vec.begin(), vec.end(), val );
		if ( it == vec.end() )
			return no_index;
		else return it - vec.begin();
	}

}
