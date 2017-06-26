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
		const prop_node literal_pn( "a=appel;b=123" );
		FLUT_TEST( literal_pn.get< string >( "a" ) == "appel" );
		FLUT_TEST( literal_pn.get< int >( "b" ) == 123 );

		enum class enumclass { value1, value2, value3 };
		enum normalenum { value1, value2, value3 };

		enumclass e1 = enumclass::value3;
		normalenum e2 = value2;

		flut::prop_node pn;
		pn.set( "empty", "" );
		pn.set( "key with spaces", "value with spaces\nand \"special\" \001 characters" );
		pn.push_back( "test", 1.2 );
		auto a = pn.get< float >();

		std::vector< custom_struct > vec;
		for ( int i = 1; i <= 3; ++i ) vec.push_back( custom_struct( stringf( "name%d", i ), i * 1.5 ) );
		pn.push_back( "vec_test", vec );

		std::vector< math::vec3f > vec2;
		for ( int i = 1; i <= 3; ++i ) vec2.push_back( math::vec3d( i, i * 1.1, i * 1.11 ) );
		pn.push_back( "vec2_test", vec2 );

		pn.push_back( "e1", e1 );
		pn.push_back( "e2", e2 );

		auto vec1b = pn.get< std::vector< custom_struct > >( "vec_test" );
		auto vec2b = pn.get< std::vector< math::vec3f > >( "vec2_test" );

		FLUT_TEST( e1 == pn.get< enumclass >( "e1" ) );
		FLUT_TEST( e2 == pn.get< normalenum >( "e2" ) );

		prop_node p2;
		p2.set( "test", pn );
		FLUT_TEST( p2.get_child( "test" ) == pn );

		// test delimiters
		pn.set_delimited( "this.is.a.subfolder", 1.5 );
		FLUT_TEST( pn[ "this" ][ "is" ][ "a" ][ "subfolder" ].get< double >() == 1.5 );
		FLUT_TEST( pn.get_delimited< double >( "this.is.a.subfolder" ) == 1.5 );

		save_prop( pn, "prop_node_test.prop" );
		auto pn_loaded = load_prop( "prop_node_test.prop" );

		if ( !FLUT_TEST( pn == pn_loaded ) )
		{
			log::info( pn );
			log::info( pn_loaded );
		}
	}
}
