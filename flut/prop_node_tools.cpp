#include "prop_node_tools.hpp"

#include <contrib/rapidxml-1.13/rapidxml.hpp>
#include <fstream>

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

	prop_node FLUT_API load_xml( const string& filename )
	{
		string file_contents = load_string( filename );
		rapidxml::xml_document<> doc;
		doc.parse< 0 >( &file_contents[ 0 ] ); // not officially supported but probably safe

		if ( doc.first_node() )
		{
			prop_node pn;
			pn.add_child( doc.first_node()->name(), read_rapid_xml_node( doc.first_node() ) );
			return pn;
		}
		else return prop_node();
	}

	bool is_valid_prop_label( const string& s )
	{
		return ( s.size() > 0 && isalpha( s[ 0 ] ) );
	}

	string get_prop_token( char_stream& str )
	{
		while ( true )
		{
			string t = str.get_token( "={};" );
			if ( t.empty() ) return t;
			if ( t[ 0 ] == ';' )
			{
				// comment: skip rest of line
				str.get_line();
				continue;
			}
			else return t;
		}
	}

	void read_prop_node( char_stream& str, prop_node& parent )
	{
		string t = get_prop_token( str );
		if ( t == "=" )
		{
			parent.set_value( get_prop_token( str ) );
		}
		else if ( t == "{" )
		{
			while ( str.good() && t != "}" )
			{
				t = get_prop_token( str );
				if ( is_valid_prop_label( t ) )
					read_prop_node( str, parent.add_child( t ) );
				else if ( t != "}" )
					flut_error( "Invalid token: " + t );
			}
		}
	}

	prop_node FLUT_API load_prop( const string& filename )
	{
		auto str = load_char_stream( filename );
		prop_node root;
		string t = get_prop_token( str );
		while ( is_valid_prop_label( t ) )
		{
			read_prop_node( str, root.add_child( t ) );
			t = get_prop_token( str );
		}
		return root;
	}

	void write_prop_none( std::ostream& str, const string& label, const prop_node& pn, int level, bool readable )
	{
		string indent = readable ? string( level, '\t' ) : "";
		string newline = readable ? "\n" : " ";
		string assign = readable ? " = " : "=";

		str << indent << label;
		if ( pn.has_value() )
			str << assign << '\"' << pn.get_value() << '\"'; // #TODO only add quotes when needed
		str << newline;
		if ( pn.has_children() )
		{
			str << indent << "{" << newline;
			for ( auto& node : pn )
				write_prop_none( str, node.first, node.second, level + 1, readable );
			str << indent << "}" << newline;
		}
	}

	void FLUT_API save_prop( const prop_node& pn, const string& filename, bool readable )
	{
		std::ofstream str( filename );
		for ( auto& node : pn )
		{
			write_prop_none( str, node.first, node.second, 0, readable );
		}
	}
}
