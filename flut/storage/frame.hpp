#pragma once

namespace flut
{
	namespace storage
	{
		template< typename BufferT< typename StorageT > >
		struct frame
		{
			frame() {}
			virtual ~frame() {}
		};
	}
}
