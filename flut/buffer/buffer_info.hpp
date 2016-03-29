#pragma once

#include <unordered_map>
#include <vector>
#include "flut/system/types.hpp"

namespace flut
{
	template< typename T >
	struct buffer_info
	{
		buffer_info() {}
		~buffer_info() {}

		index_t add_channel( const T& label ) {
			index_t idx = find_channel( label );
			if ( idx == no_index ) {
				headers.push_back( label );
				header_indices[ label ] = headers.size() - 1;
				return headers.size() - 1;
			}
			else return idx;
		}
		size_t channel_count() const { return headers.size(); }
		index_t find_channel(const T& label) const {
			auto it = header_indices.find( label );
			return ( it != header_indices.end() ) ? it->second : no_index;
		}

	private:
		std::vector< T > headers;
		std::unordered_map< T, index_t > header_indices;
	};

	template<>
	struct buffer_info< void >
	{
		index_t add_channel() { return count++; }
		index_t count;
	};
}
