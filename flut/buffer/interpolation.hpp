#pragma once

#include "flut/math/vec3_type.hpp"
#include <utility>
#include <vector>
#include "buffer_access.hpp"
#include "flut/system/assert.hpp"
#include <xtr1common>

namespace flut
{
	template< typename T >
	typename buffer_access<T>::value_t interpolated_value( const T& cont, typename buffer_access<T>::key_t key )
	{
		flut_assert( !cont.empty() );

		auto ub = buffer_access<T>::upper_bound( cont, key );
		if ( ub == cont.cend() )
			return buffer_access<T>::value_ref( --ub ); // key is beyond data, return last sample
		else if ( ub == cont.cbegin() )
			return buffer_access<T>::value_ref( ub ); // key is before data, return first sample
		else
		{
			// interpolate between two samples (lb and ub)
			auto lb = ub - 1;
			buffer_access<T>::key_t uw = ( key - lb->first ) / ( ub->first - lb->first );
			return ( buffer_access<T>::key_t(1) - uw ) * buffer_access<T>::value_ref( lb ) + uw * buffer_access<T>::value_ref( ub );
		}
	}

	template< typename T, typename K >
	T interpolated_value( const std::vector< T >& cont, K key, typename std::enable_if< !buffer_access< std::vector< T > >::value >::type* = 0 ) 
	{
		flut_assert( !cont.empty() );

		if ( key < K(0) )
			return cont.front();
		else
		{
			auto lb = size_t( key );
			auto ub = lb + 1;
			if ( ub >= cont.size() )
				return cont.back();

			K w = key - lb;
			return ( K(1) - w ) * cont[ lb ] + w * cont[ ub ];
		}
	}
}
