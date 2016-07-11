#pragma once

namespace flut
{
	void prop_node_test()
	{
		flut::prop_node pn;
		pn.set( 1.2 );
		pn.add( "test", 1.2 );
		auto a = pn.get< float >();

		// TODO: add a proper test
		auto props = read_xml( "../../../config/f0914_walk_GH.xml" );
		std::cout << props;
	}
}
