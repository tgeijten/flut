#pragma once

#include "flut/system/types.hpp"

namespace flut
{
	template< typename C >
	typename C::iterator find( C& cont, typename C::value_type& e )
	{ return std::find( std::begin( cont ), std::end( cont ), e ); }

	template< typename C, typename P >
	typename C::const_iterator find( const C& cont, typename C::value_type& e )
	{ return std::find( std::begin( cont ), std::end( cont ), e ); }

	template< typename C, typename P >
	typename C::iterator find_if( C& cont, P pred )
	{ return std::find_if( std::begin( cont ), std::end( cont ), pred ); }

	template< typename C, typename P >
	typename C::const_iterator find_if( const C& cont, const P pred )
	{ return std::find_if( std::cbegin( cont ), std::cend( cont ), pred ); }

	template< typename C >
	typename C::iterator min_element( C& cont )
	{ return std::min_element( std::begin( cont ), std::end( cont ) ); }

	template< typename C >
	typename C::const_iterator min_element( const C& cont )
	{ return std::min_element( std::cbegin( cont ), std::cend( cont ) ); }

	template< typename C >
	typename C::iterator max_element( C& cont )
	{ return std::max_element( std::begin( cont ), std::end( cont ) ); }

	template< typename C >
	typename C::const_iterator max_element( const C& cont )
	{ return std::max_element( std::cbegin( cont ), std::cend( cont ) ); }

	template< typename T >
	index_t find_index( const vector< T >& vec, const T& val )
	{
		auto it = std::find( vec.begin(), vec.end(), val );
		if ( it == vec.end() )
			return no_index;
		else return it - vec.begin();
	}

	template< typename T >
	T median( const vector< T >& vec )
	{
		auto s = vec.size();
		flut_assert( s > 0 );
		if ( ( s & 1 ) == 0 ) return vec[ s / 2 ];
		else return ( vec[ s / 2 ] + vec[ s / 2 - 1 ] ) / T(2);
	}

	template< typename It, typename Pr >
	struct view_if
	{
		view_if( It first, It last, Pr pred ) : first_( first ), last_( last ), pred_( pred ) {}
		struct iterator
		{
			iterator( const view_if& cv, It pos ) : cv_( cv ), pos_( pos ) { next_match(); }

			void next_match() { while ( pos_ != cv_.last_ && !cv_.pred_( *pos_ ) ) ++pos_; }
			iterator& operator++() { ++pos_; next_match(); return *this; }
			iterator operator++( int ) { auto keepit = *this; ++pos_; next_match(); return keepit; }
			bool operator==( const iterator& other ) { return pos_ == other.pos_; }
			bool operator!=( const iterator& other ) { return pos_ != other.pos_; }
			typename It::value_type operator*() const { return *pos_; }
			const view_if& cv_;
			It pos_;
		};

		iterator begin() const { return iterator( *this, first_ ); }
		iterator end() const { return iterator( *this, last_ ); }

		It first_, last_;
		Pr pred_;
	};

	template< typename It, typename Pr > view_if< It, Pr > make_view_if( It first, It last, Pr pred ) {
		return view_if< It, Pr >( first, last, pred );
	}

	template< typename C, typename Pr > view_if< typename C::iterator, Pr > make_view_if( C& cont, Pr pred ) {
		return view_if< typename C::iterator, Pr >( cont.begin(), cont.end(), pred );
	}
}
