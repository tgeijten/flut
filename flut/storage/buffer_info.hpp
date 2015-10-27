#pragma once

#include "../types.hpp"
#include <unordered_map>
#include <vector>

namespace fluc
{
	namespace data
	{
		struct buffer_info
		{
			buffer_info() {}
			~buffer_info() {}

			index_t add_channel( const string& label ) {
				index_t idx = find_channel( label );
				if ( idx == no_index ) {
					labels.push_back( label );
					label_indices[ label ] = labels.size() - 1;
					return labels.size() - 1;
				}
				else return idx;
			}
			size_t channel_count() const { return labels.size(); }
			index_t find_channel(const string& label) const {
				auto it = label_indices.find( label );
				return ( it != label_indices.end() ) ? it->second : no_index;
			}

		private:
			std::vector< string > labels;
			std::unordered_map< string, index_t > label_indices;
		};
	}
}
