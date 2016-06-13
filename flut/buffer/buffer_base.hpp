#pragma once

#include <unordered_map>
#include <vector>
#include "flut/system/types.hpp"

namespace flut
{
	template< class C, typename H >
	struct buffer_base
	{
		buffer_base( size_t channels = 0 ) : headers( channels ) {}
		~buffer_base() {}

		index_t add_channel( const H& label ) {
			index_t idx = find_channel( label );
			if ( idx == no_index ) {
				headers.push_back( label );
				header_indices[ label ] = headers.size() - 1;
				static_cast< C* >( this )->resize_buffer();
				return headers.size() - 1;
			}
			else return idx;
		}
		size_t channel_count() const { return headers.size(); }
		index_t find_channel( const H& label ) const {
			auto it = header_indices.find( label );
			return ( it != header_indices.end() ) ? it->second : no_index;
		}

	private:
		std::vector< H > headers;
		std::unordered_map< H, index_t > header_indices;
	};

	template< class C >
	struct buffer_base< C, void >
	{
		buffer_base( size_t channels = 0 ) : count( channels ) { }
		index_t add_channel() { ++count; static_cast< C* >( this )->resize_buffer(); return count - 1; }
		size_t channel_count() const { return count; }

	private:
		index_t count;
	};
}
