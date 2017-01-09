#pragma once

#include <memory>
#include <functional>
#include <map>

#include "prop_node.hpp"

namespace flut
{
	template< typename T, class ...Args >
	class factory
	{
	public:
		typedef std::function< std::unique_ptr< T >( Args... ) > create_func_t;

		// get create func
		create_func_t& operator()( const string& type ) {
			auto it = factory_functions.find( type );
			flut_error_if( it == factory_functions.end(), "Unregistered type: " + type );
			return it->second;
		}

		// register class
		template< typename U >
		void register_class( const string name ) {
			factory_functions[ name ] = []( Args... args ) { return std::unique_ptr< T >( new U( args... ) ); };
		}

		bool empty() { return factory_functions.empty();  }

	private:
		std::map< string, create_func_t > factory_functions;
	};
}
