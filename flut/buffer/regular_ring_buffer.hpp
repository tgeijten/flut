#pragma once

#include "buffer_base.hpp"
#include "flut/system/assert.hpp"

namespace flut
{
	template< typename T, size_t F, typename L = void >
	class regular_ring_buffer 
	{
	public:
		regular_ring_buffer( size_t channels ) : data( F * channels ), curframe( 0 ), bufinf( channels ) {}
		~regular_ring_buffer() {}

		index_t add_frame() { return ++curframe; }
		size_t frame_count() { return curframe + 1; }
		size_t channel_count() { return bufinf.channel_count(); }

		void set_value( index_t channel, const T& value ) { data[ curframe * channel_count() + channel_count() ] = value; }

		const T* get_frame( index_t frame ) {
			flut_assert( frame >= frame_count() - F && frame < frame_count() );
			return data[ ( frame % F ) * channel_count() ];
		}

		T get_value( index_t frame, index_t channel ) {
			flut_assert( frame >= frame_count() - F && frame < frame_count() && channel < channel_count() );
			return data[ ( frame % F ) * channel_count() + channel ];
		}

		T get_interpolated_value( index_t frame0, index_t channel, T pos ) {
			flut_assert( frame0 >= frame_count() - F && frame0 < frame_count() && channel < channel_count() );
			index_t ofs0 = ( frame0 % F ) * channel_count() + channel;
			index_t ofs1 = ( ( frame0 + 1 ) % F ) * channel_count() + channel;
			return ( T(1) - pos ) * data[ ofs0 ] + pos * data[ ofs1 ];
		}

	private:
		std::vector< T > data;
		index_t curframe;
	};
}
