#pragma once

#include "flut/system/platform.hpp"
#include "flut/system/types.hpp"
#include "flut/string_tools.hpp"

#ifdef FLUT_COMP_MSVC
#	pragma warning( push )
#	pragma warning( disable: 4251 )
#endif

namespace flut
{
	class prop_node;

	template< typename T > struct prop_node_converter {
		static T get( const prop_node& pn ) { return from_str< T >( pn.get_value() ); }
		static void set( prop_node& pn, const T& value ) { pn.set_value( to_str< T >( value ) ); }
	};

	template< typename T > struct prop_node_converter< vector< T > > {
		static vector< T > get( const prop_node& pn ) {
			vector< T > vec;
			for ( auto& p : pn )
				vec.push_back( p.second.get< T >() );
			return vec;
		}
		static void set( prop_node& pn, const vector< T >& vec ) {
			for ( size_t i = 0; i < vec.size(); ++i )
				pn.add_child( stringf( "e%d", i ), make_prop_node( vec[ i ] ) );
		}
	};

	template< typename T > prop_node make_prop_node( const T& value );

	class FLUT_API prop_node
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
		template< typename T > T get() const { return prop_node_converter< T >::get( *this ); }

		/// get the value of a child node
		template< typename T > T get( const key_t& key ) const { return prop_node_converter< T >::get( get_child( key ) ); }

		/// get the value of a child node, or a default value if it doesn't exist
		template< typename T > T get( const key_t& key, const T& def ) const
		{ const auto it = find( key ); if ( it != end() ) return it->second.get< T >(); else return def; }

		/// see if this has a value
		bool has_value() const { return !value.empty(); }

		/// access value_t value
		const value_t& get_value() const { return value; }
		void set_value( value_t&& val ) { value = std::move( val ); }
		void set_value( const value_t& val ) { value = val; }

		/// add a node with a value
		template< typename T > prop_node& add( const key_t& key, const T& value )
		{ children.push_back( std::make_pair( key, make_prop_node( value ) ) ); return children.back().second; }

		/// add a child node
		prop_node& add_child( const key_t& key, const prop_node& pn )
		{ children.push_back( std::make_pair( key, pn ) ); return children.back().second; }
		prop_node& add_child( const key_t& key, prop_node&& pn )
		{ children.push_back( std::make_pair( key, std::move( pn ) ) ); return children.back().second; }

		/// reserve children
		void reserve( size_t n ) { children.reserve( n ); }

		/// set the value of this node
		template< typename T > prop_node& set( const T& v ) { prop_node_converter< T >::set( *this, v ); return *this; }

		/// set the value of a child node, the node is created if not existing
		template< typename T > prop_node& set( const key_t& key, const T& v )
		{ auto it = find( key ); if ( it == end() ) add_child( key, make_prop_node( v ) ); else it->second.set( v ); return *this; }

		/// get a child node, throws exception if not existing
		const prop_node& get_child( const key_t& key ) const
		{ auto it = find( key ); flut_assert_msg( it != end(), "Could not find key: " + key ); return it->second; }
		prop_node& get_child( const key_t& key )
		{ auto it = find( key ); flut_assert_msg( it != end(), "Could not find key: " + key ); return it->second; }

		/// access child by name
		const prop_node& operator[]( const key_t& key ) const { return get_child( key ); }
		prop_node& operator[]( const key_t& key ) { return get_child( key ); }

		/// access child by index
		const prop_node& operator[]( index_t idx ) const { flut_assert( idx < size() ); return children[ idx ].second; }
		prop_node& operator[]( index_t idx ) { flut_assert( idx < size() ); return children[ idx ].second; }
		size_t size() const { return children.size(); }

		/// find a child node
		iterator find( const key_t& key ) { return std::find_if( begin(), end(), [&]( const pair_t& e ) { return e.first == key; } ); }
		const_iterator find( const key_t& key ) const { return std::find_if( begin(), end(), [&]( const pair_t& e ) { return e.first == key; } ); }

		/// begin of child nodes
		iterator begin() { return children.begin(); }
		const_iterator begin() const { return children.begin(); }

		/// end of child nodes
		iterator end() { return children.end(); }
		const_iterator end() const { return children.end(); }

		/// output node and children to stream (nicely aligned)
		std::ostream& to_stream( std::ostream& str, int depth = 0, int key_align = 0 ) const;

	private:
		int get_align_width( int depth ) const;

		value_t value;
		container_t children;
	};

	/// make a prop_node with a value
	template< typename T > prop_node make_prop_node( const T& value ) { return prop_node().set( value ); }

	/// stream operator
	inline std::ostream& operator<<( std::ostream& str, const prop_node& pn )
	{ pn.to_stream( str ); return str; }
}

#ifdef FLUT_COMP_MSVC
#	pragma warning( pop )
#endif
