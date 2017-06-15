#pragma once

#include "flut/dynarray.hpp"
#include "flut/system/assert.hpp"

namespace flut
{
	template< typename T >
	class circular_deque
	{
	public:
		circular_deque( size_t buf_size = 0 ) : front_( 0 ), size_( 0 ), buffer_( buf_size ) {}
		~circular_deque() {}

		void push_back( const T& value ) {
			if ( ++size_ > capacity() ) buffer_.insert( buffer_.begin() + ( front_ + size_ - 1 ), value );
			else back() = value;
		}
		void push_front( const T& value ) {
			if ( ++size_ > capacity() ) buffer_.insert( buffer_.begin() + front_, value );
			else { front_ = ( front_ + capacity() - 1 ) % capacity(); front() = value; }
		}

		void pop_back() { flut_assert( size_ > 0 ); --size_; }
		void pop_front() { flut_assert( size_ > 0 ); front_ = ( front_ + 1 ) % capacity(); --size_; }

		T& back() { flut_assert( size_ > 0 ); return buffer_[ ( front_ + size_ - 1 ) % capacity() ]; }
		const T& back() const { flut_assert( size_ > 0 ); return buffer_[ ( front_ + size_ ) % capacity() ]; }

		T& front() { flut_assert( size_ > 0 ); return buffer_[ front_ ]; }
		const T& front() const { flut_assert( size_ > 0 ); return buffer_[ front_ ]; }

		size_t size() const { return size_; }

		bool empty() const { return size_ == 0; }
		void clear() { front_ = size_ = 0; }

		void reserve( size_t s ) { buffer_.resize( s ); }
		size_t capacity() const { return buffer_.size(); }

		template< typename IT > struct iterator_impl : public std::iterator< std::forward_iterator_tag, IT >
		{
			typedef IT value_type;
			iterator_impl( size_t index, std::vector< IT >& buffer ) : index_( index ), buffer_( buffer ) {}
			size_t index_;
			vector< IT >& buffer_;
			iterator_impl< IT >& operator++() const { return ++index_; }
			iterator_impl< IT >& operator++( int ) { auto ret = *this; ++index_; return ret; }
			bool operator==( const iterator& other ) { return other.index_ == index_; }
			bool operator!=( const iterator& other ) { return other.index_ != index_; }
			IT operator*() { return buffer_[ index_ % buffer_.size() ]; }
		};
		using iterator = iterator_impl< T >;
		using const_iterator = iterator_impl< const T >;

		iterator begin() { return iterator( front_, buffer_ ); }
		iterator end() { return iterator( front_ + size_, buffer_ ); }
		const_iterator begin() const { return const_iterator( front_, buffer_ ); }
		const_iterator end() const { return const_iterator( front_ + size_, buffer_ ); }

	private:
		size_t front_;
		size_t size_;

		std::vector< T > buffer_;
	};
}
