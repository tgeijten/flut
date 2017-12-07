#pragma once

#include "system/types.hpp"

namespace flut
{
	template< typename T >
	class dictionary
	{
	public:
		typedef std::pair< T, string > pair_t;

		dictionary() {}
		dictionary( std::initializer_list< pair_t > l ) : data( l ) {}
		~dictionary() {}

		/// lookup name of element e
		const string& operator()( const T& e ) {
			auto it = std::find_if( data.begin(), data.end(), [&]( pair_t& p ) { return e == p.first; } );
			flut_error_if( it == data.end(), "Could not find element " + to_str( e ) );
			return it->second;
		}

		/// lookup element with name str
		const T& operator()( const string& str ) {
			auto it = std::find_if( data.begin(), data.end(), [&]( pair_t& p ) { return str == p.second; } );
			flut_error_if( it == data.end(), "Could not find element with name " + str );
			return it->first;
		}

		/// lookup element with name str or return default
		const T& operator()( const string& str, const T& value_not_found ) {
			auto it = std::find_if( data.begin(), data.end(), [&]( pair_t& p ) { return str == p.second; } );
			return ( it == data.end() ) ? value_not_found : it->first;
		}

	private:
		std::vector< pair_t > data;
	};

	template< typename T >
	dictionary< T > make_dictionary( std::initializer_list< std::pair< T, string > > l ) { return dictionary< T >( l ); }

	template< typename T >
	T lookup( const string& value, std::initializer_list< std::pair< const char*, T > > table )
	{
		for ( auto& entry : table )
			if ( value == entry.first )
				return entry.second;
		flut_error( "Could not find " + value );
	}
}
