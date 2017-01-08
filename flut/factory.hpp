#pragma once

#include <memory>
#include "prop_node.hpp"

namespace flut
{
	template< typename T >
	class factory
	{
	public:
		typedef std::function< controller_info*( const prop_node& ) > create_func_t;

		// create instance
		std::unique_ptr< T > operator( const prop_node& pn ) const;

	private:
		std::map< string, create_func_t > factory_functions;
	};
}
