#pragma once

#include "flut/system/types.hpp"

namespace flut
{
	template< typename C, typename P >
	typename C::iterator find_if( C& cont, P pred )
	{ return std::find_if( std::begin( cont ), std::end( cont ), pred ); }

	template< typename C, typename P >
	typename C::const_iterator find_if( const C& cont, const P pred )
	{ return std::find_if( std::cbegin( cont ), std::cend( cont ), pred ); }

	template< typename C >
	typename C::iterator min_element( C& cont )
	{ return std::min_element( std::begin( cont ), std::end( cont ) ); }

	template< typename C >
	typename C::const_iterator min_element( const C& cont )
	{ return std::min_element( std::cbegin( cont ), std::cend( cont ) ); }

	template< typename T >
	index_t find_index( const vector< T >& vec, const T& val )
	{
		auto it = std::find( vec.begin(), vec.end(), val );
		if ( it == vec.end() )
			return no_index;
		else return it - vec.begin();
	}
}
