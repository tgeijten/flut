#pragma once

#include "flut/types.hpp"

namespace flut
{
	template< typename KeyT = string, typename ValueT = string >
	class propnode
	{
	public:
		propnode() {}
		virtual ~propnode() {}
		
	private:
		ValueT value;
		std::vector< std::pair< KeyT, propnode > > children;
	};
}
