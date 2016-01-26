#pragma once

#include "buffer_info.hpp"

namespace 
{
	template< typename T >
	class regular_ring_buffer 
	{
	public:
		regular_ring_buffer( const buffer_info& bi, size_t frames ) : data( frames * bi.channel_count() ) {}
		~regular_ring_buffer() {}

		void add_frame( const std::vector< T >& frame ) {
			flut_assert( frame.size() == bufinf.channel_count() );
			data.insert( data.end(), frame.begin(), frame.end() );
		}

		index_t add_frame( T value = T( 0 ) ) { return ++curframe; }
		void set_value( index_t channel, const T& value ) { data[ data.size() - bufinf.channel_count() + channel ] = value; }
		const T* get_frame( index_t frame ) { flut_assert( frame < frame_count() ); }
		size_t frame_count() { return data.size() / bufinf.channel_count(); }


	private:
		const buffer_info& bufinf;
		std::vector< T > data;
		index_t curframe;
	};
}
