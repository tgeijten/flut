#pragma once

#include "flut/system/assert.hpp"

namespace flut
{
	template< typename T, typename L = void >
	class frame_buffer : public buffer_base< frame_buffer< T, L >, L >
	{
	public:
		frame_buffer( size_t channels ) : buffer_base< frame_buffer< T, L >, L >( channels ), data( channels ) {}
		~frame_buffer() {}

		/// add empty frame to the buffer
		void add_frame( T value = T( 0 ) ) { data.insert( data.end(), this->channel_count(), value ); }

		/// add a specific frame to the buffer (DO WE NEED THIS?)
		void add_frame( const std::vector< T >& frame )
		{ flut_assert( frame.size() == this->channel_count() ); data.insert( data.end(), frame.begin(), frame.end() ); }
		
		/// number of frames in the buffer
		size_t frame_count() { return data.size() / this->channel_count(); }

		/// set a value for a channel in the most recent frame
		void set_value( index_t channel, const T& value ) { data[ data.size() - this->channel_count() + channel ] = value; }

		/// get access to the data in the most recent frame (DO WE NEED THIS?)
		const T* get_frame( index_t frame )
		{ flut_assert( frame < frame_count() ); return &data[ frame * this->channel_count() ]; }

		/// get the value of a specific frame / channel
		T get_value( index_t frame, index_t channel )
		{ flut_assert( frame < frame_count() && channel < this->channel_count() ); return &data[ frame * this->channel_count() + channel ]; }

		/// get the interpolated value of a specific frame / channel
		T get_interpolated_value( index_t frame0, index_t channel, T pos ) {
			flut_assert( frame0 + 1 < frame_count() );
			index_t ofs = frame0 * this->channel_count() + channel;
			return ( T(1) - pos ) * data[ ofs ] + pos * data[ ofs + this->channel_count() ];
		}

		/// function for internal maintenance, DO NOT CALL this directly
		/// it is public because of its specific use of CRTP
		void resize_buffer() {
			flut_assert_msg( frame_count() <= 1, "Channels can only be added when there's at most one frame in the buffer" );
			data.resize( this->channel_count() );
		}

	private:
        std::vector< T > data;
	};
}
