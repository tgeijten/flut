#pragma once
#include "flut/system/types.hpp"
#include "flut/string_tools.hpp"
#include "flut/system/test_framework.hpp"
#include "flut/system/path.hpp"
#include "flut/dictionary.hpp"
#include "flut/hash.hpp"

namespace flut
{
	void string_test()
	{
		enum fruit { no_fruit, appel, peer, banaan, fruit_count };
		auto fruit_dict = flut::dictionary< fruit >( { { appel, "appel" }, { peer, "peer" }, { banaan, "banaan" } } );

		FLUT_TEST( fruit_dict( "appel", no_fruit ) == appel );
		FLUT_TEST( fruit_dict( "peer", no_fruit ) == peer );
		FLUT_TEST( fruit_dict( "banaan", no_fruit ) == banaan );
		FLUT_TEST( fruit_dict( "peerr", no_fruit ) == no_fruit );

		for ( int f = appel; f < fruit_count; ++f )
		{
			switch ( hash( fruit_dict( fruit( f ) ) ) )
			{
			case "appel"_hash: FLUT_TEST( f == appel ); break;
			case "peer"_hash: FLUT_TEST( f == peer ); break;
			case "banaan"_hash: FLUT_TEST( f == banaan ); break;
			default: FLUT_TEST_MSG( 1 == 2, "hash error" );
			}
		}

		string s = "Test 0.123 24";
		string a;
		double d;
		int i;
		scan_str( s, a, d, i );
		FLUT_TEST( a == "Test" );
		FLUT_TEST( d == 0.123 );
		FLUT_TEST( i == 24 );

		auto vs = split_str( s, " " );
		FLUT_TEST( vs[ 0 ] == "Test" );
		FLUT_TEST( vs[ 1 ] == "0.123" );
		FLUT_TEST( vs[ 2 ] == "24" );

		auto vs2 = flut::split_str( "appel; peer,,, banaan", ";., " );
		FLUT_TEST( vs2[ 0 ] == "appel" );
		FLUT_TEST( vs2[ 1 ] == "peer" );
		FLUT_TEST( vs2[ 2 ] == "banaan" );

		auto nasty_string = string( "String with \"quotes\" and spaces\nand\tspecial\001\002\003characters" );
		auto quoted_nasty = try_quoted( nasty_string );
		auto unquoted_nasty = try_unquoted( quoted_nasty );
		FLUT_TEST( nasty_string == unquoted_nasty );

		path p( "X:/appel/taart.txt" );
		FLUT_TEST( p.empty() == false );
		FLUT_TEST( p.extension() == "txt" );
		FLUT_TEST( p.replace_extension( "new_ext" ).str() == "X:/appel/taart.new_ext" );
		FLUT_TEST( p.filename() == "taart.new_ext");
		FLUT_TEST( p.stem() == "taart");
		FLUT_TEST( path( "foo/bar.txt" ).stem() == "bar" );
		FLUT_TEST( path( "foo/.bar" ).stem() == "" );
		FLUT_TEST( p.replace_filename( "new" ) == "X:/appel/new" );
		FLUT_TEST( path( "X:/test" ) / "bla" == "X:/test/bla" );
		FLUT_TEST( path( "X:/test/" ) / "bla" == "X:/test/bla" );
		FLUT_TEST( path( "X:\\test\\bla" ).make_preferred() == "X:/test/bla" );
	}
}
