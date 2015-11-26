#pragma once

namespace flut
{
	template< typename KeyT, typename ValueT >
	ValueT interpolated_value( const std::vector< std::pair< KeyT, ValueT > >& cont, KeyT key )
	{
		auto ub = std::upper_bound( cont.cbegin(), cont.cend(), key, []( KeyT lhs, const std::pair< KeyT, ValueT >& rhs) { return lhs < rhs.first; } );
		if ( ub == cont.cend() )
			return cont.back().second;
		else if ( ub == cont.cbegin() )
			return ub->second;
		else
		{
			auto ul = ub - 1;
			KeyT uw = ( key - ul->first ) / ( ub->first - ul->first );
			return ( KeyT(1) - uw ) * ul->second + uw * ub->second;
		}
	}
}
