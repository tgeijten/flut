#pragma once

#include <memory>
#include <functional>
#include "system/platform.hpp"
#include "vecmap.hpp"

// need for demangling with GCC
#ifndef FLUT_COMP_MSVC
#	include <cxxabi.h>
#endif

namespace flut
{
	template< typename T >
	string clean_type_name()
	{
#ifdef FLUT_COMP_MSVC
		string str = typeid( T ).name();
#else
		const char* typeInfo = typeid ( T ).name();
		int status;
		char* cleanType = abi::__cxa_demangle( typeInfo, 0, 0, &status );
		string str = String( cleanType );
		free( cleanType );
#endif
		size_t pos = str.find_last_of( ": " );
		if ( pos != std::string::npos )
			return str.substr( pos + 1 );
		else return str;
	}

	template< typename T, class ...Args >
	class factory
	{
	public:
		typedef std::function< std::unique_ptr< T >( Args... ) > create_func_t;

		// get create func
		create_func_t& get( const string& type ) {
			auto it = factory_functions.find( type );
			flut_error_if( it == factory_functions.end(), "Unregistered type: " + type );
			return it->second;
		}

		// aliases
		create_func_t& operator()( const string& type ) { return get( type ); }
		create_func_t& operator[]( const string& type ) { return get( type ); }

		// register class
		template< typename U >
		void register_class( const string& name = clean_type_name<U>() ) {
			factory_functions[ name ] = []( Args... args ) { return std::unique_ptr< T >( new U( args... ) ); };
		}

		bool empty() { return factory_functions.empty();  }

	private:
		flut::vecmap< string, create_func_t > factory_functions;
	};
}
