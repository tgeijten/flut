#pragma once

#include "flut/prop_node_tools.hpp"
#include <iostream>
#include "flut/math/vec3_type.hpp"

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
		for ( int i = 1; i <= 3; ++i ) vec.push_back( custom_struct( stringf( "name%d", i ), i * 1.5 ) );
		pn.add( "vec_test", vec );

		std::vector< math::vec3f > vec2;
		for ( int i = 1; i <= 3; ++i ) vec2.push_back( math::vec3d( i, i * 1.1, i * 1.11 ) );
		pn.add( "vec2_test", vec2 );

		std::cout << pn << std::endl;

		auto vec1b = pn.get< std::vector< custom_struct > >( "vec_test" );
		auto vec2b = pn.get< std::vector< math::vec3f > >( "vec2_test" );

		// TODO: add a proper test
		//auto props = read_xml( "../../../config/f0914_walk_GH.xml" );
		//std::cout << props;
	}
}
