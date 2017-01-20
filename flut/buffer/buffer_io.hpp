#pragma once

#include <fstream>
#include "frame_buffer.hpp"

namespace flut
{
	template< typename T, typename L >
	std::ostream& operator<<( std::ostream& str, const frame_buffer< T, L >& buf )
	{
		for ( index_t i = 0; i < buf.frame_count(); ++i )
		{
			auto f = buf.get_frame( i );
			auto channels = buf.channel_count();

			for ( index_t ci = 0; ci < channels; ++ci )
				str << f[ ci ] << ( ci < channels - 1 ? '\t' : std::endl );
		}
	}
}
