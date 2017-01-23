#pragma once

#include <unordered_map>
#include <vector>
#include "flut/system/types.hpp"

namespace flut
{
	template< class C, typename H >
	struct buffer_base
	{
		buffer_base( size_t channels = 0 ) : labels_( channels ) {}
		~buffer_base() {}

		index_t add_channel( const H& label ) {
			index_t idx = find_channel( label );
			if ( idx == no_index ) {
				static_cast<C*>( this )->resize_buffer();
				labels_.push_back( label );
				label_indices_[ label ] = labels_.size() - 1;
				return labels_.size() - 1;
			}
			else return idx;
		}

		size_t channel_count() const { return labels_.size(); }

		index_t find_channel( const H& label ) const {
			auto it = label_indices_.find( label );
			return ( it != label_indices_.end() ) ? it->second : no_index;
		}

		const H& get_channel_label( index_t idx ) const { return labels_[ idx ];  }
		void set_channel_label( index_t idx, const H& header ) { labels_[ idx ] = header; }

	private:
		std::vector< H > labels_;
		std::unordered_map< H, index_t > label_indices_;
	};

	template< class C >
	struct buffer_base< C, void >
	{
		buffer_base( size_t channels = 0 ) : num_channels( channels ) { }
		index_t add_channel() { ++num_channels; static_cast< C* >( this )->resize_buffer(); return num_channels - 1; }
		size_t channel_count() const { return num_channels; }
		index_t get_channel_label( index_t idx ) { return idx; }

	private:
		index_t num_channels;
	};
}
