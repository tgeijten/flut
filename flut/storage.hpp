#pragma once

#include "flut/system/types.hpp"
#include "flut/system/assert.hpp"

namespace flut
{
	/// Simple storage class for storing frames with channels of data
	template< typename T, typename L = string >
	class storage
	{
	public:
		storage( size_t frames = 0, size_t channels = 0, T value = T( 0 ) ) : frame_size_( frames ), labels_( channels ), data_( channels * frames, value ) {}
		~storage() {}

		/// add a channel and resize buffer if needed
		index_t add_channel( L label ) { resize( frame_size(), channel_size() + 1 ); labels_.back() = label; return channel_size() - 1; }

		/// add a channel with data, resize buffer if needed
		index_t add_channel( L label, const vector< T >& data ) {
			resize( std::max( frame_size(), data.size() ), channel_size() + 1 );
			labels_.back() = label;
			auto cidx = channel_size() - 1;
			for ( index_t fidx = 0; fidx < data.size(); ++fidx ) ( *this )( fidx, cidx ) = data[ fidx ];
			return cidx;
		}

		/// set channel label
		void set_label( index_t channel, L label ) { labels_[ channel ] = label;  }

		/// get channel label
		const L& get_label( index_t channel ) const { return labels_[ channel ]; }

		/// find index of a label
		index_t find_channel( const L& label ) const { auto it = std::find( labels_.begin(), labels_.end(), label ); return ( it != labels_.end() ) ? it - labels_.begin(): no_index; }

		/// add frame to storage
		void add_frame( T value = T( 0 ) ) { data_.resize( data_.size() + channel_size(), value ); ++frame_size_; }

		/// add frame to storage
		void add_frame( const vector< T >& data ) {
			flut_assert( data.size() == channel_size() );
			data_.resize( data_.size() + channel_size() );
			++frame_size_;
			std::copy( data.begin(), data.end(), data_.end() - channel_size() );
		}

		/// number of channels
		size_t channel_size() const { return labels_.size(); }

		/// number of frames in storage
		size_t frame_size() const { return frame_size_; }

		/// check if there is any data
		bool empty() const { return data_.empty(); }

		/// access value with bounds checking
		T& at( index_t frame, index_t channel )
		{ flut_assert( frame < frame_size() && channel < channel_size() ); return data_[ frame * channel_size() + channel ]; }
		const T& at( index_t frame, index_t channel ) const
		{ flut_assert( frame < frame_size() && channel < channel_size() ); return data_[ frame * channel_size() + channel ]; }

		/// access value (no bounds checking)
		T& operator()( index_t frame, index_t channel ) { return data_[ frame * channel_size() + channel ]; }
		const T& operator()( index_t frame, index_t channel ) const { return data_[ frame * channel_size() + channel ]; }

		/// access value of most recent frame
		T& operator[]( index_t channel ) { flut_assert( !data_.empty() ); return at( frame_size() - 1, channel ); }
		const T& operator[]( index_t channel ) const { flut_assert( !data_.empty() ); return at( frame_size() - 1, channel ); }

		/// access value of most recent frame by channel name, add channel if not existing
		T& operator[]( const L& label ) {
			auto idx = find_channel( label );
			if ( idx == no_index ) idx = add_channel( label );
			return (*this)[ idx ];
		}

		/// access value of most recent frame by channel name
		const T& operator()( const L& label ) const { return *this( find_channel( label ) ); }

		/// get access to the data in a specific frame (DO WE NEED THIS?)
		const T* get_frame( index_t frame = frame_size() - 1 )
		{ flut_assert( frame < frame_size() ); return &data_[ frame * this->channel_size() ]; }

		/// get the interpolated value of a specific frame / channel
		T get_interpolated_value( T frame_idx, index_t channel ) {
			auto frame_f = floor( frame_idx );
			auto frame_w = frame_idx - frame_f;
			index_t frame0 = static_cast<index_t>( frame_f );
			flut_assert( frame0 + 1 < frame_size() );
			index_t ofs = frame0 * this->channel_size() + channel;
			return ( T(1) - frame_w ) * data_[ ofs ] + frame_w * data_[ ofs + this->channel_size() ];
		}

		void resize( size_t nframes, size_t nchannels, T value = T(0) ) {
			flut_error_if( nframes < frame_size() || nchannels < channel_size(), "Cannot shrink storage" );
			if ( nchannels > channel_size() ) {
				if ( frame_size() > 1 ) {
					// reorganize existing data
					std::vector< T > new_data( nchannels * nframes, value );
					for ( index_t fi = 0; fi < frame_size(); ++fi )
						for ( index_t ci = 0; ci < channel_size(); ++ci )
							new_data[ nchannels * fi + ci ] = data_[ channel_size() * fi + ci ];
					data_ = std::move( new_data );
				}
				else data_.resize( nframes * nchannels, value ); // just resize

				labels_.resize( nchannels );
				frame_size_ = nframes;
			}
			else {
				// just resize data
				data_.resize( nframes * nchannels, value );
				frame_size_ = nframes;
			}
		}

		const std::vector< L >& labels() const { return labels_; }
		const std::vector< T >& data() const { return data_; }

	private:
		size_t frame_size_;
		std::vector< L > labels_;
		std::vector< T > data_;
	};

	template< typename T, typename L > std::ostream& operator<<( std::ostream& str, const storage< T, L >& buf )
	{
		for ( index_t ci = 0; ci < buf.channel_size(); ++ci ) {
			str << buf.get_label( ci );
			if ( ci == buf.channel_size() - 1 ) str << std::endl; else str << '\t';
		}

		for ( index_t fi = 0; fi < buf.frame_size(); ++fi ) {
			for ( index_t ci = 0; ci < buf.channel_size(); ++ci ) {
				str << buf( fi, ci );
				if ( ci == buf.channel_size() - 1 ) str << std::endl; else str << '\t';
			}
		}
		return str;
	}
}
