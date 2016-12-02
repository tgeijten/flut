#include "prop_node_tools.hpp"

#include <contrib/rapidxml-1.13/rapidxml.hpp>
#include <contrib/rapidxml-1.13/rapidxml_print.hpp>
#include <fstream>
#include "system/path.hpp"
#include "string_tools.hpp"

namespace flut
{
	FLUT_API prop_node load_file( const path& filename )
	{
		if ( filename.extension() == "xml" )
			return load_xml( filename );
		else return load_prop( filename );
	}

	prop_node get_rapid_xml_node( rapidxml::xml_node<>* node )
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
				pn.add_child( child->name(), get_rapid_xml_node( child ) );
		}

		return pn;
	}

	void set_rapid_xml_node( rapidxml::xml_document<>& doc, rapidxml::xml_node<>* xmlnode, const prop_node& pn )
	{
		if ( pn.has_value() )
			xmlnode->value( pn.get_value().c_str() );

		for ( auto& child : pn )
		{
			xmlnode->append_node( doc.allocate_node( rapidxml::node_element, child.first.c_str() ) );
			set_rapid_xml_node( doc, xmlnode->last_node(), child.second );
		}
	}

	FLUT_API prop_node load_xml( const path& filename )
	{
		string file_contents = load_string( filename );
		rapidxml::xml_document<> doc;
		doc.parse< 0 >( &file_contents[ 0 ] ); // not officially supported but probably safe

		if ( doc.first_node() )
		{
			prop_node pn;
			pn.add_child( doc.first_node()->name(), get_rapid_xml_node( doc.first_node() ) );
			return pn;
		}
		else return prop_node();
	}

	FLUT_API void save_xml( const prop_node& pn, const path& filename )
	{
		rapidxml::xml_document<> doc;
		set_rapid_xml_node( doc, &doc, pn );
		std::ofstream ostr( filename.str() );
		ostr << doc;

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

	FLUT_API prop_node load_prop( const path& filename )
	{
		auto str = load_char_stream( filename.str() );
		prop_node root;
		string t = get_prop_token( str );
		while ( is_valid_prop_label( t ) )
		{
			read_prop_node( str, root.add_child( t ) );
			t = get_prop_token( str );
		}
		return root;
	}

	FLUT_API prop_node load_ini( const path& filename )
	{
		prop_node pn;
		prop_node* cur_group = &pn;

		auto str = load_char_stream( filename.str() );
		for ( string t = str.get_token( "=" ); str.good(); t = str.get_token( "=" ) )
		{
			if ( t.size() == 0 )
				continue;

			if ( t[0] == '#' )
			{
				str.get_line();
				continue;
			}

			if ( t.size() > 2 && t[ 0 ] == '[' && t[ t.size() -1 ] == ']' )
			{
				cur_group = &pn.add_child( t.substr( 1, t.size() - 2 ) );
				continue;
			}

			// must be a key = value line
			string t2 = str.get_token( "=" );
			flut_error_if( t == "=", "Error loading ini file, expected '='" );
			t2 = str.get_token( "=" );
			cur_group->set( t, t2 );
		}
		return pn;
	}

	FLUT_API void save_ini( const prop_node& pn, const path& filename )
	{
		std::ofstream str( filename.str() );
		for ( auto& e : pn )
		{
			if ( e.second.has_children() ) // group item
			{
				str << '[' << e.first << ']' << std::endl;
				for ( auto& e2 : e.second )
					str << e2.first << " = " << e2.second << std::endl;
			}
			else if ( e.second.has_value() ) // main item
				str << e.first << " = " << e.second << std::endl;
		}
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
			str << indent << "{" << newline; // #TODO only do newline when needed
			for ( auto& node : pn )
				write_prop_none( str, node.first, node.second, level + 1, readable );
			str << indent << "}" << newline;
		}
	}

	FLUT_API void save_prop( const prop_node& pn, const path& filename, bool readable )
	{
		std::ofstream str( filename.str() );
		for ( auto& node : pn )
		{
			write_prop_none( str, node.first, node.second, 0, readable );
		}
	}

	void merge_prop_nodes( prop_node& pn, const prop_node& other, bool overwrite )
	{
		for ( auto& o : other )
		{
			auto it = pn.find_child( o.first );
			if ( it == pn.end() )
				pn.add_child( o.first, o.second );
			else if ( overwrite )
				it->second = o.second;
		}
	}

	void resolve_include_files( prop_node &pn, const path &filename, const string& include_directive, int level )
	{
		for ( auto iter = pn.begin(); iter != pn.end(); )
		{
			if ( iter->first == include_directive )
			{
				// load included file using filename path
				path include_path = filename.parent_path() / iter->second.get< path >( "file" );
				bool merge_children = iter->second.get< bool >( "merge_children", false );
				auto included_props = load_file_with_include( include_path, include_directive, level + 1 );

				// remove the include node
				iter = pn.erase( iter );

				// merge or include, depending on options
				if ( merge_children )
				{
					merge_prop_nodes( pn, included_props, false );
					iter = pn.begin(); // reset the iterator, which has become invalid after merge
				}
				else
				{
					// insert the children at the INCLUDE spot
					iter = pn.insert_children( iter, included_props.begin(), included_props.end() );
				}
			}
			else
			{
				// search in children
				resolve_include_files( iter->second, filename, include_directive, level );
				++iter;
			}
		}
	}

	prop_node load_file_with_include( const path& filename, const string& include_directive, int level )
	{
		flut_error_if( level >= 100, "Exceeded maximum include level, check for loops in includes" );

		prop_node pn = load_file( filename );
		resolve_include_files( pn, filename, include_directive, level );

		return pn;
	}
}
