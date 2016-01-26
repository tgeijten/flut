#pragma once

#include "../system/assert.hpp"

namespace flut
{
	template< typename T >
	class regular_buffer 
	{
	public:
		regular_buffer( const buffer_info& bi ) : bufinf( bi ) {}
		~regular_buffer() {}

		void add_frame( const std::vector< T >& frame ) {
			flut_assert( frame.size() == bufinf.channel_count() );
			data.insert( data.end(), frame.begin(), frame.end() );
		}

		void add_frame( T value = T( 0 ) ) { data.insert( data.end(), bufinf.channel_count(), value ); }
		void set_value( index_t channel, const T& value ) { data[ data.size() - bufinf.channel_count() + channel ] = value; }
		const T* get_frame( index_t frame ) { flut_assert( frame < frame_count() ); }
		size_t frame_count() { return data.size() / bufinf.channel_count(); }

	private:
		const buffer_info& bufinf;
		std::vector< T > data;
	};
}
