#include "prop_node_tools.hpp"

#include <contrib/rapidxml-1.13/rapidxml.hpp>

namespace flut
{
	prop_node read_rapid_xml_node( rapidxml::xml_node<>* node )
	{
		// make new prop_node
		prop_node pn = make_prop_node( node->value() );

		// add attributes
		for ( rapidxml::xml_attribute<>* attr = node->first_attribute(); attr; attr = attr->next_attribute() )
			pn.add( attr->name(), attr->value() );

		// add child nodes
		for ( rapidxml::xml_node<>* child = node->first_node(); child; child = child->next_sibling() )
		{
			if ( child->name_size() > 0 )
				pn.add_child( child->name(), read_rapid_xml_node( child ) );
		}

		return pn;
	}

	prop_node FLUT_API read_xml( const string& filename )
	{
		string file_contents = load_string( filename );
		rapidxml::xml_document<> doc;
		doc.parse< 0 >( &file_contents[ 0 ] ); // not officially supported but probably safe

		prop_node pn;
		pn.add_child( doc.first_node()->name(), read_rapid_xml_node( doc.first_node() ) );

		return pn;
	}
}
