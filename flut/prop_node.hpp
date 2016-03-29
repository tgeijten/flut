#pragma once

#include "flut/system/types.hpp"

namespace flut
{
	template< typename KeyT = string, typename ValueT = string >
	class prop_node
	{
	public:
		prop_node() {}
		virtual ~prop_node() {}
		
	private:
		ValueT value;
		std::vector< std::pair< KeyT, prop_node > > children;
	};
}
