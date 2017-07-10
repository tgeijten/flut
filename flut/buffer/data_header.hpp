#pragma once

#include <unordered_map>
#include <vector>
#include "flut/system/types.hpp"
#include "../system/assert.hpp"

namespace flut
{
	template< typename L >
	struct data_header
	{
		data_header( size_t channels = 0 ) : labels_( channels ) {}
		data_header( std::initializer_list< L > labels ) : labels_( labels ) {}
		data_header( const std::vector< L >& labels ) : labels_( labels ) {}
		~data_header() {}

		index_t add( const L& label ) {
			flut_assert( find_index( label ) == no_index );
			labels_.push_back( label );
			return label_indices_[ label ] = labels_.size() - 1;
		}

		index_t get_or_add( const L& label ) {
			index_t idx = find_index( label );
			if ( idx == no_index ) {
				return add( label )
			}
			else return idx;
		}

		void resize( size_t s ) { flut_assert( s >= size() ); labels_.resize( s ); }
		void clear() { labels_.clear(); label_indices_.clear(); }

		size_t size() const { return labels_.size(); }

		index_t find_index( const L& label ) const {
			auto it = label_indices_.find( label );
			return ( it != label_indices_.end() ) ? it->second : no_index;
		}

		const L& operator[]( index_t idx ) const { return labels_[ idx ]; }

		index_t set( index_t idx, const L& label ) {
			flut_assert( idx < size() && find_index( label ) == no_index );
			labels_[ idx ] = label;
			label_indices_[ label ] = labels_.size() - 1;
			return idx;
		}

		index_t set_back( const L& label ) { return set( labels.size() - 1, label ); }

		typename vector< L >::const_iterator begin() const { return labels_.begin(); }
		typename vector< L >::const_iterator end() const { return labels_.end(); }

	private:
		std::vector< L > labels_;
		std::unordered_map< L, index_t > label_indices_;
	};

	template<> struct data_header< void >
	{
		data_header( size_t channels = 0 ) : num_channels( channels ) { }
		size_t size() const { return num_channels; }
		index_t add() { return num_channels++; }
		index_t get_label( index_t idx ) const { return idx; }

	private:
		index_t num_channels;
	};
}
