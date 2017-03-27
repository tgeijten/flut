#pragma once

namespace flut
{
	template< typename K, typename V >
	class vecmap : public std::vector< std::pair< K, V > >
	{
	public:
		typedef typename std::vector< std::pair< K, V > >::value_type value_type;

		typename std::vector< std::pair< K, V > >::iterator find( const K& key ) {
			return std::find_if( this->begin(), this->end(), [&]( value_type& kvp ) { return kvp.first == key; } );
		}

		typename std::vector< std::pair< K, V > >::const_iterator find( const K& key ) const {
			return std::find_if( this->cbegin(), this->cend(), [&]( value_type& kvp ) { return kvp.first == key; } );
		}

		V& operator[]( const K& key ) {
			auto it = find( key );
			if ( it == this->end() ) {
				this->emplace_back( key, V( 0 ) );
				return this->back().second;
			}
			else return it->second;
		}

		const V& operator[]( const K& key ) const {
			auto it = find( key );
			flut_error_if( it == this->end(), "Could not find key" );
			return it->second;
		}
	};
}
