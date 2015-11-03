#pragma once

namespace flut
{
	namespace storage
	{
		template< typename BufferT< typename DataT > >
		struct frame
		{
			frame() {}
			virtual ~frame() {}
		};
	}
}
