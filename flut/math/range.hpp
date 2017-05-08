#pragma once

#include <xutility>

namespace flut
{
	template< int B, int E, int S = 1 >
	class irange
	{
	public:
		struct iterator : public std::iterator< std::forward_iterator_tag, int >
		{
			typedef int value_type;
			iterator( int v ) : value_( v ) {}
			int value_;
			int operator-( const iterator& other ) { return ( value_ - other.value_ ) / S; }
			int operator++() { value_ += S; flut_assert( value_ <= E ); return value_; }
			int operator++( int ) { value_ += S; flut_assert( value_ <= E ); return value_ - S; }
			bool operator==( const iterator& other ) { return other.value_ == value_; }
			bool operator!=( const iterator& other ) { return other.value_ != value_; }
			int operator*() { return value_; }
		};

		iterator begin() const { return iterator( B ); }
		iterator end() const { return iterator( E ); }
	};
}
