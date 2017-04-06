#pragma once

#include "flut/flat_map.hpp"
#include "flut/system/types.hpp"
#include "flut/sorted_vector.hpp"

namespace flut
{
	void container_test()
	{
		struct sortable
		{
			int e;
			std::string s;
			bool operator<( const sortable& other ) const { if ( e == other.e ) return s < other.s; else return e < other.e; }
		};

		sorted_vector< sortable > sv;
		sv.insert( sortable{ 3, "peer" } );
		sv.insert( sortable{ 1, "appel" } );
		sv.insert( sortable{ 2, "banaan" } );
		sv.insert( sortable{ 3, "banaan" } );
		sv.insert( sortable{ 1, "banaan" } );

		for ( auto& e : sv )
			cout << e.e << e.s << endl;

		flat_map< string, int > vm;
		vm[ "Appel" ] = 1;
		vm[ "Peer" ] = 2;
		vm[ "Banaan" ] = 3;

		FLUT_TEST( vm[ "Appel" ] == 1 );
		FLUT_TEST( vm[ "Peer" ] == 2 );
		FLUT_TEST( vm[ "Banaan" ] == 3 );
	}
}
