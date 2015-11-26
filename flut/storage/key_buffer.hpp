#pragma once

#include <algorithm>
#include <utility>
#include <vector>

namespace flut
{
	template< typename KeyT, typename ValueT >
	struct key_buffer
	{
	public:
		typedef KeyT key_t;
		typedef ValueT value_t;
		typedef std::pair< KeyT, ValueT > pair_t;

		key_buffer() {}
		~key_buffer() {}

		void push_back( const KeyT& key, const ValueT& value ) { data.push_back( pair_t( key, value ) ); }

		std::vector< pair_t > data;
		//iter_t test( key_t key ) const
		//{ return std::upper_bound( data.cbegin(), data.cend(), key, []( key_t lhs, const pair_t& rhs) { return lhs < rhs.first; } ) };

	};
}
