#pragma once

#include "flut/vecmap.hpp"
#include "flut/system/types.hpp"

namespace flut
{
	void container_test()
	{
		vecmap< string, int > vm;
		vm[ "Appel" ] = 1;
		vm[ "Peer" ] = 2;
		vm[ "Banaan" ] = 3;

		FLUT_TEST( vm[ "Appel" ] == 1 );
		FLUT_TEST( vm[ "Peer" ] == 2 );
		FLUT_TEST( vm[ "Banaan" ] == 3 );
	}
}
