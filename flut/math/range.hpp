#pragma once

#include <xutility>

namespace flut
{
	template< typename T >
	struct range
	{
		range() : begin_( T( 0 ) ), end_( T( 0 ) ) {}
		range( T b, T e ) : begin_( b ), end_( e ) {}

		struct iterator : public std::iterator< std::forward_iterator_tag, int >
		{
			typedef T value_type;
			iterator( T v ) : value_( v ) {}
			T value_;
			T operator-( const iterator& other ) { return value_ - other.value_; }
			T operator++() { return ++value_; }
			T operator++( int ) { return value++; }
			bool operator==( const iterator& other ) { return other.value_ == value_; }
			bool operator!=( const iterator& other ) { return other.value_ != value_; }
			T operator*() { return value_; }
		};

		iterator begin() const { return iterator( begin_ ); }
		iterator end() const { return iterator( end_ ); }

		T begin_, end_;
	};

	template< typename T >
	struct step_range
	{
		step_range( T b, T e, T s = T( 1 ) ) : begin_( b ), end_( e ), step_( s ) {}
		step_range( const range< T >& r, T s = T( 1 ) ) : begin_( r.begin_ ), end_( r.end_ ), step_( s ) {}

		struct iterator : public std::iterator< std::forward_iterator_tag, int >
		{
			typedef T value_type;
			iterator( T v, T s ) : value_( v ), step_( s ) {}
			T value_, step_;
			T operator-( const iterator& other ) { return ( value_ - other.value_ ) / step_; }
			T operator++() { return value_ += step_; }
			T operator++( int ) { value_ += step_; return value_ - step_; }
			bool operator==( const iterator& other ) { return other.value_ == value_; }
			bool operator!=( const iterator& other ) { return other.value_ != value_; }
			T operator*() { return value_; }
		};

		iterator begin() const { return iterator( begin_, step_ ); }
		iterator end() const { return iterator( end_, step_ ); }

		T begin_, end_, step_;
	};

	// TODO: SFINAE to make sure it's integer
	template< typename T > range< T > make_range( T b, T e ) { return range< T >( b, e ); }
	template< typename T > step_range< T > make_range( T b, T e, T s ) { return step_range< T >( b, e, s ); }
	template< typename T > step_range< T > make_range( const range< T >& r, T s ) { return step_range< T >( r, s ); }
}
