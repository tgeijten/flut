#pragma once

#include "string_tools.hpp"
#include "flut/system/platform.hpp"
#include "flut/system/types.hpp"
#include "flut/system/assert.hpp"
#include "flut/system/string_cast.hpp"
#include <algorithm>

#ifdef FLUT_COMP_MSVC
#	pragma warning( push )
#	pragma warning( disable: 4251 )
#endif

namespace flut
{
	class prop_node; 

	/// make a prop_node with a value
	template< typename T > prop_node make_prop_node( const T& value );

    /// forward declare prop_node_cast
	template< typename T, typename E = void > struct prop_node_cast;

	/// prop_node class
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
		prop_node( const value_t& v ) : value( v ) {}
		prop_node( value_t&& v ) : value( std::move( v ) ) {}
		prop_node( const prop_node& other ) : value( other.value ), children( other.children ) {}
		prop_node( prop_node&& other ) : value( std::move( other.value ) ), children( std::move( other.children ) ) {}

		/// destructor (non-virtual)
		~prop_node() {}

		/// assignment operators
		prop_node& operator=( const prop_node& other ) { value = other.value; children = other.children; return *this; }
		prop_node& operator=( prop_node&& other ) { value = std::move( other.value ); children = std::move( other.children ); return *this; }

		/// get the value of this node
		template< typename T > T get() const { return prop_node_cast< T >::from( *this ); }

		/// get the value of a child node
		template< typename T > T get( const key_t& key ) const { return prop_node_cast< T >::from( get_child( key ) ); }

		/// get the value of a child node, or a default value if it doesn't exist
		template< typename T > T get( const key_t& key, const T& def ) const
		{ const auto it = find_child( key ); if ( it != end() ) return it->second.get< T >(); else return def; }

		/// see if this prop_node has a value
		bool has_value() const { return !value.empty(); }

		/// see if this prop_node has children
		bool has_children() const { return !children.empty(); }
		bool has_child( const key_t& key ) const { return find_child( key ) != end(); }

		/// see if this prop_node is empty
		bool empty() const { return value.empty() && children.empty(); }
		void clear() { value.clear(); children.clear(); }

		/// access value_t value
		const value_t& get_value() const { return value; }
		void set_value( value_t&& val ) { value = std::move( val ); }
		void set_value( const value_t& val ) { value = val; }

		/// add a node with a value
		template< typename T > prop_node& add( const key_t& key, const T& value )
		{ children.push_back( std::make_pair( key, make_prop_node( value ) ) ); return children.back().second; }

		/// add a child node
		prop_node& add_child( const key_t& key, const prop_node& pn )
		{ children.emplace_back( std::make_pair( key, pn ) ); return children.back().second; }
		prop_node& add_child( const key_t& key, prop_node&& pn )
		{ children.emplace_back( std::make_pair( key, std::move( pn ) ) ); return children.back().second; }
		prop_node& add_child( const key_t& key )
		{ children.emplace_back( std::make_pair( key, prop_node() ) ); return children.back().second; }

		/// insert children
		const_iterator insert_children( const_iterator pos, const_iterator first, const_iterator last )
		{ return children.insert( pos, first, last ); }

		iterator insert_children( iterator pos, const_iterator first, const_iterator last )
		{ return children.insert( pos, first, last ); }

		/// reserve children
		void reserve( size_t n ) { children.reserve( n ); }

		/// set the value of this node
		template< typename T > prop_node& set( const T& v ) { *this = prop_node_cast< T >::to( v ); return *this; }

		/// set the value of a child node, the node is created if not existing
		template< typename T > prop_node& set( const key_t& key, const T& v )
		{ auto it = find_child( key ); if ( it == end() ) add_child( key, make_prop_node( v ) ); else it->second.set( v ); return *this; }

		/// get a child node, throws exception if not existing
		const prop_node& get_child( const key_t& key ) const
		{ auto it = find_child( key ); flut_error_if( it == end(), "Could not find key: " + key ); return it->second; }
		prop_node& get_child( const key_t& key )
		{ auto it = find_child( key ); flut_error_if( it == end(), "Could not find key: " + key ); return it->second; }

		/// get a child node, return nullptr if not existing
		const prop_node* try_get_child( const key_t& key ) const { auto it = find_child( key ); return it != end() ? &(it->second) : nullptr; }
		prop_node* try_get_child( const key_t& key ) { auto it = find_child( key ); return it != end() ? &(it->second) : nullptr; }

		/// access child by name
		const prop_node& operator[]( const key_t& key ) const { return get_child( key ); }
		prop_node& operator[]( const key_t& key ) { auto it = find_child( key ); if ( it != end() ) return it->second; else return add_child( key ); }

		/// access child by index
		const prop_node& operator[]( index_t idx ) const { flut_assert( idx < size() ); return children[ idx ].second; }
		prop_node& operator[]( index_t idx ) { flut_assert( idx < size() ); return children[ idx ].second; }
		size_t size() const { return children.size(); }

		/// find a child node
		iterator find_child( const key_t& key ) { return std::find_if( begin(), end(), [&]( const pair_t& e ) { return e.first == key; } ); }
		const_iterator find_child( const key_t& key ) const { return std::find_if( begin(), end(), [&]( const pair_t& e ) { return e.first == key; } ); }

		/// begin of child nodes
		iterator begin() { return children.begin(); }
		const_iterator begin() const { return children.begin(); }
		const_iterator cbegin() const { return children.cbegin(); }

		/// end of child nodes
		iterator end() { return children.end(); }
		const_iterator end() const { return children.end(); }
		const_iterator cend() const { return children.cend(); }

		/// erase a child
		iterator erase( const_iterator it ) { return children.erase( it ); }

		/// see if this node has been accessed (touched)
		bool touched() const { return touch; }
		size_t count_untouched() const { size_t t = touched() ? 0 : 1; for ( auto& c : children ) t += count_untouched(); return t; }

	private:
		bool touch;
		value_t value;
		container_t children;
	};

    /// prop_node_cast and specializations
	template< typename T, typename E > struct prop_node_cast {
		static T from( const prop_node& pn ) { return string_cast< T, E >::from( pn.get_value() ); }
		static prop_node to( const T& value ) { return prop_node( string_cast< T, E >::to( value ) ); }
	};

	template< typename T > struct prop_node_cast< vector<T> > {
		static vector<T> from( const prop_node& pn )
		{ vector<T> vec; for ( auto& p : pn ) vec.push_back( p.second.get<T>() ); return vec; }
		static prop_node to( const vector<T>& vec )
		{ prop_node pn; for ( size_t i = 0; i < vec.size(); ++i ) pn.add_child( stringf( "item%d", i ), make_prop_node( vec[ i ] ) ); return pn; }
	};

	template< typename T > struct prop_node_cast< T, typename std::enable_if< std::is_enum< T >::value >::type > {
		static T from( const prop_node& pn ) { return static_cast<T>( from_str<int>( pn.get_value() ) ); }
		static prop_node to( const T& v ) { return prop_node( to_str( static_cast<int>( v ) ) ); }
	};


	template< typename T > prop_node make_prop_node( const T& value ) { return prop_node().set( value ); }

	/// stream operator
	FLUT_API std::ostream& to_stream( std::ostream& str, const prop_node& pn, int depth = 0, int key_align = 0 );
	inline std::ostream& operator<<( std::ostream& str, const prop_node& pn ) { return to_stream( str, pn ); }
}

#ifdef FLUT_COMP_MSVC
#	pragma warning( pop )
#endif
