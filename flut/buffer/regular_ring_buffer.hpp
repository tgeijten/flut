#pragma once

#include "buffer_base.hpp"
#include "flut/system/assert.hpp"

namespace flut
{
	template< typename T, typename L = void >
	class regular_ring_buffer : public buffer_base< regular_ring_buffer< T, L >, L > 
	{
	public:
		regular_ring_buffer( size_t channels = 0, size_t frames = 0 ) : data( frames * channels ), num_frames( frames), cur_frame( 0 ), buffer_base< regular_ring_buffer< T, L >, L >( channels ) {}
		~regular_ring_buffer() {}

		index_t add_frame() { return ++cur_frame; }
		size_t frame_count() { return cur_frame + 1; }

		void set_frame_size( size_t frames ) { num_frames = frames; resize_buffer(); }

		void resize_buffer() {
			flut_assert_msg( cur_frame == 0, "regular_ring_buffer can only be resized when empty" );
			data.resize( num_frames * this->channel_count() );
		}

		void set_value( index_t channel, const T& value ) { data[ cur_frame * this->channel_count() + this->channel_count() ] = value; }

		const T* get_frame( index_t frame ) {
			flut_assert( frame >= frame_count() - num_frames && frame < frame_count() );
			return data[ ( frame % num_frames ) * this->channel_count() ];
		}

		T get_value( index_t frame, index_t channel ) {
			flut_assert( frame >= frame_count() - num_frames && frame < frame_count() && channel < this->channel_count() );
			return data[ ( frame % num_frames ) * this->channel_count() + channel ];
		}

		T get_interpolated_value( index_t frame0, index_t channel, T pos ) {
			flut_assert( frame0 >= frame_count() - num_frames && frame0 < frame_count() && channel < this->channel_count() );
			index_t ofs0 = ( frame0 % num_frames ) * this->channel_count() + channel;
			index_t ofs1 = ( ( frame0 + 1 ) % num_frames ) * this->channel_count() + channel;
			return ( T(1) - pos ) * data[ ofs0 ] + pos * data[ ofs1 ];
		}

	private:
        std::vector< T > data;
		size_t num_frames;
		index_t cur_frame;
	};
}
