#include "prop_node.hpp"

#include <contrib/rapidxml-1.13/rapidxml.hpp>
#include <stdio.h>
#include <memory>
#include <iomanip>

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

	std::ostream& prop_node::to_stream( std::ostream& str, int depth, int align ) const
	{
		if ( align == 0 )
			align = get_align_width( depth );

		for ( auto& child : children )
		{
			string key_str( depth * 2, ' ' );
			key_str += child.first;

			str << std::left << std::setw( align ) << key_str;
			if ( child.second.has_value() || child.second.children.size() == 0 )
				str << std::setw( 0 ) << " = " << child.second.get_value();
			str << std::endl;

			child.second.to_stream( str, depth + 1, align );
		}

		return str;
	}

	int prop_node::get_align_width( int depth ) const
	{
		int width = 0;
		for ( auto& child : children )
		{
			width = std::max( width, depth * 2 + int( child.first.size() ) );
			width = std::max( width, child.second.get_align_width( depth + 1 ) );
		}
		return width;
	}
}
