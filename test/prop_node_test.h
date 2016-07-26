#pragma once

#include "flut/prop_node_tools.hpp"
#include <iostream>

namespace flut
{
	struct custom_struct
	{
		custom_struct( const string& n, double v ) : name( n ), value ( v ) {}
		string name;
		double value;
	};


	template<> struct prop_node_converter< custom_struct > {
		static custom_struct get( const prop_node& pn )
		{
			return custom_struct( pn.get<string>( "name" ), pn.get<double>( "value" ) );
		}
		static void set( prop_node& pn, const custom_struct& value )
		{
			pn.set( "name", value.name );
			pn.set( "value", value.value );
		}
	};

	void prop_node_test()
	{
		flut::prop_node pn;
		pn.set( 1.2 );
		pn.add( "test", 1.2 );
		auto a = pn.get< float >();

		std::vector< custom_struct > vec;
		for ( int i = 0; i < 10; ++i ) vec.push_back( custom_struct( stringf( "name%d", i ), i * 1.5 ) );
		pn.add( "vec_test", vec );
		std::cout << pn << std::endl;

		auto vec2 = pn.get< std::vector< custom_struct > >( "vec_test" );

		// TODO: add a proper test
		auto props = read_xml( "../../../config/f0914_walk_GH.xml" );
		std::cout << props;
	}
}
