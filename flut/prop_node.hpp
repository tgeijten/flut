#pragma once

#include "flut/types.hpp"
#include "flut/string_tools.hpp"

namespace flut
{
	class prop_node;
	template< typename T > prop_node make_prop_node( const T& value );

	class prop_node
	{
	public:
		typedef string key_t;
		typedef string value_t;
		typedef std::pair< key_t, prop_node > pair_t;
		typedef std::vector< pair_t > container_t;
		typedef container_t::iterator iterator;
		typedef container_t::const_iterator const_iterator;

		/// constructors
		prop_node() {}
		prop_node( const prop_node& other ) : value( other.value ), children( other.children ) {}
		prop_node( prop_node&& other ) : value( std::move( other.value ) ), children( std::move( other.children ) ) {}

		/// destructor (non-virtual)
		~prop_node() {}

		/// assignment operators
		prop_node& operator=( const prop_node& other ) { value = other.value; children = other.children; return *this; }
		prop_node& operator=( prop_node&& other ) { value = std::move( other.value ); children = std::move( other.children ); return *this; }

		/// get the value of this node
		template< typename T > T get() const { return from_str< T >( value ); }

		/// get the value of a child node
		template< typename T > T get( const key_t& key ) const { return get_child( key ).get< T >(); }

		/// get the value of a child node, or a default value if it doesn't exist
		template< typename T > T get( const key_t& key, const T& def ) const
		{ auto it = find( key ); if ( it ) return it->second.get< T >(); else return def; }

		/// add a node with a value
		template< typename T > prop_node& add( const key_t& key, const T& value )
		{ children.push_back( std::make_pair( key, make_prop_node( value ) ) ); return children.back().second; }

		/// set the value of this node
		template< typename T > prop_node& set( const T& v ) { value = to_str( v ); return *this; }

		/// set the value of a child node, the node is created if not existing
		template< typename T > prop_node& set( const key_t& key, const T& v )
		{ auto it = find( key ); if ( it == end() ) add( key, value ); else it->second.set( value ); }

		/// get a child node, throws exception if not existing
		prop_node& get_child( const key_t& key ) {
			auto it = find( key );
			flut_assert_msg( it != end(), "Could not find key: " + key );
			return it->second;
		}

		/// find a child node
		iterator find( const key_t& key ) { std::find_if( begin(), end(), [&]( const pair_t& e ) { return e.first == key; } ); }
		const_iterator find( const key_t& key ) const { std::find_if( begin(), end(), [&]( const pair_t& e ) { return e.first == key; } ); }

		/// begin of child nodes
		iterator begin() { return children.begin(); }
		const_iterator begin() const { return children.begin(); }

		/// end of child nodes
		iterator end() { return children.end(); }
		const_iterator end() const { return children.end(); }

	private:
		value_t value;
		container_t children;
	};

	/// make a prop_node with a value
	template< typename T > prop_node make_prop_node( const T& value ) { return prop_node().set( value ); }

	/// load the contents of an xml file into a prop_node
	prop_node load_xml( const string& filename );
}
