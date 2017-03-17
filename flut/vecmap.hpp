#pragma once

namespace flut
{
	template< typename K, typename V >
	class vecmap : public std::vector< std::pair< K, V > >
	{
	public:
		iterator find( const K& key ) {
			return std::find_if( begin(), end(), [&]( value_type& kvp ) { return kvp.first == key; } );
		}

		const_iterator find( const K& key ) const {
			return std::find_if( cbegin(), cend(), [&]( value_type& kvp ) { return kvp.first == key; } );
		}

		V& operator[]( const K& key ) {
			auto it = find( key );
			if ( it == end() ) {
				emplace_back( key, V( 0 ) );
				return back().second;
			}
			else return it->second;
		}

		const V& operator[]( const K& key ) const {
			auto it = find( key );
			flut_error_if( it == end(), "Could not find key" );
			return it->second;
		}
	};
}
