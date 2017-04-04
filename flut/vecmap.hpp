#pragma once

namespace flut
{
	template< typename K, typename V >
	class vecmap : private std::vector< std::pair< K, V > >
	{
	public:
		using typename std::vector< std::pair< K, V > >::value_type;
		using typename std::vector< std::pair< K, V > >::iterator;
		using typename std::vector< std::pair< K, V > >::const_iterator;

		using std::vector< std::pair< K, V > >::empty;
		using std::vector< std::pair< K, V > >::clear;
		using std::vector< std::pair< K, V > >::size;
		using std::vector< std::pair< K, V > >::begin;
		using std::vector< std::pair< K, V > >::end;
		using std::vector< std::pair< K, V > >::cbegin;
		using std::vector< std::pair< K, V > >::cend;
		using std::vector< std::pair< K, V > >::front;
		using std::vector< std::pair< K, V > >::back;
		using std::vector< std::pair< K, V > >::erase;

		iterator find( const K& key ) {
			return std::find_if( begin(), end(), [&]( const value_type& kvp ) { return kvp.first == key; } );
		}

		const_iterator find( const K& key ) const {
			return std::find_if( cbegin(), cend(), [&]( const value_type& kvp ) { return kvp.first == key; } );
		}

		V& operator[]( const K& key ) {
			auto it = find( key );
			if ( it == this->end() ) {
				this->emplace_back( key, V( 0 ) );
				return this->back().second;
			}
			else return it->second;
		}

		V& at( const K& key ) {
			auto it = find( key );
			flut_error_if( it == end(), "Could not find key: " + to_str( key ) );
			return it->second;
		}

		const V& at( const K& key ) const {
			auto it = find( key );
			flut_error_if( it == end(), "Could not find key: " + to_str( key ) );
			return it->second;
		}
	};
}
