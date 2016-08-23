#pragma once
#include "flut/system/types.hpp"
#include "flut/string_tools.hpp"
#include "flut/system/test_framework.hpp"

namespace flut
{
	void string_test()
	{
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
	}
}
