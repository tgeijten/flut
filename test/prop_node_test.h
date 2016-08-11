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


	template<> struct prop_node_cast< custom_struct > {
		static custom_struct from( const prop_node& pn )
		{
			return custom_struct( pn.get<string>( "name" ), pn.get<double>( "value" ) );
		}
		static prop_node to( const custom_struct& value )
		{
			prop_node pn;
			pn.set( "name", value.name );
			pn.set( "value", value.value );
			return pn;
		}
	};

	void prop_node_test()
	{
		enum class enumclass { value1, value2, value3 };
		enum normalenum { value1, value2, value3 };

		enumclass e1 = enumclass::value3;
		normalenum e2 = value2;

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

		pn.add( "e1", e1 );
		pn.add( "e2", e2 );

		auto vec1b = pn.get< std::vector< custom_struct > >( "vec_test" );
		auto vec2b = pn.get< std::vector< math::vec3f > >( "vec2_test" );

		FLUT_TEST( e1 == pn.get< enumclass >( "e1" ) );
		FLUT_TEST( e2 == pn.get< normalenum >( "e2" ) );

		log::trace( pn );
	}
}
