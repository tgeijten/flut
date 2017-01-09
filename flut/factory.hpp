#pragma once

#include <memory>
#include <functional>
#include <map>

#include "prop_node.hpp"

namespace flut
{
	template< typename T >
	class factory
	{
	public:
		typedef std::function< T*( const prop_node& ) > create_func_t;

		// create instance
		std::unique_ptr< T > operator()( const prop_node& pn ) const {
			string type = pn[ "type" ].get< string >();
			auto it = factory_functions.find( type );
			flut_error_if( it == factory_functions.end(), "Unregistered type: " + type );
			return std::unique_ptr< T >( it->second( pn ) );
		}

		// register class subtype
		template< typename U >
		void register_class( const string name ) {
			factory_functions[ name ] = []( const prop_node& pn ) { return new U( pn ); };
		}

	private:
		std::map< string, create_func_t > factory_functions;
	};
}
