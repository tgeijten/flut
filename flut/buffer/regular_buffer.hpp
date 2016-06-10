#pragma once

#include "flut/system/assert.hpp"

namespace flut
{
	template< typename T, typename L = void >
	class regular_buffer 
	{
	public:
		regular_buffer( size_t channels ) : bufinf( channels ) {}
		~regular_buffer() {}

		index_t add_channel( L name ) {
			index_t idx = bufinf.find_channel( name );
			if ( idx == no_index )
			{
				flut_assert_msg( frame_count() <= 1, "Channels can only be added when there's at most one frame in the buffer" );
				idx = bufinf.add_channel( name );
				data.resize( bufinf.channel_count() );
			}
			return idx;
		}

		void add_frame( const std::vector< T >& frame )
		{ flut_assert( frame.size() == bufinf.channel_count() ); data.insert( data.end(), frame.begin(), frame.end() ); }

		void add_frame( T value = T( 0 ) ) { data.insert( data.end(), bufinf.channel_count(), value ); }

		size_t frame_count() { return data.size() / channel_count(); }

		size_t channel_count() { return bufinf.channel_count(); }

		void set_value( index_t channel, const T& value ) { data[ data.size() - channel_count() + channel ] = value; }

		const T* get_frame( index_t frame )
		{ flut_assert( frame < frame_count() ); return &data[ frame * channel_count() ]; }

		T get_value( index_t frame, index_t channel )
		{ flut_assert( frame < frame_count() && channel < channel_count() ); return &data[ frame * channel_count() + channel ]; }

		T get_interpolated_value( index_t frame0, index_t channel, T pos ) {
			flut_assert( frame0 + 1 < frame_count() );
			index_t ofs = frame0 * channel_count() + channel;
			return ( T(1) - pos ) * data[ ofs ] + pos * data[ ofs + channel_count() ];
		}

	private:
		buffer_info< L > bufinf;
		std::vector< T > data;
	};
}
