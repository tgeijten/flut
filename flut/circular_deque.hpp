#pragma once

#include "flut/dynarray.hpp"
#include "flut/system/assert.hpp"

namespace flut
{
	template< typename T >
	class circular_deque
	{
	public:
		circular_deque( size_t buf_size = 0 ) : front_( 0 ), size_( 0 ), capacity_( buf_size ), buffer_( buf_size > 0 ? new T[ buf_size ] : nullptr ) {}
		~circular_deque() {}

		void push_back( const T& value ) { flut_assert( size_ < capacity() ); ++size_; back() = value; }
		void push_front( const T& value ) { flut_assert( size_ < capacity() );  ++size_; front_ = ( front_ + capacity() - 1 ) % capacity(); front() = value; }

		void pop_back() { flut_assert( size_ > 0 ); --size_; }
		void pop_front() { flut_assert( size_ > 0 ); front_ = ( front_ + 1 ) % capacity(); --size_; }

		T& back() { flut_assert( size_ > 0 ); return buffer_[ ( front_ + size_ - 1 ) % capacity() ]; }
		const T& back() const { flut_assert( size_ > 0 ); return buffer_[ ( front_ + size_ ) % capacity() ]; }

		T& front() { flut_assert( size_ > 0 ); return buffer_[ front_ ]; }
		const T& front() const { flut_assert( size_ > 0 ); return buffer_[ front_ ]; }

		size_t size() const { return size_; }

		bool empty() const { return size_ == 0; }
		void clear() { front_ = size_ = 0; }

		void reserve( size_t s ) { if ( s != capacity_ ) { buffer_ = ( s > 0 ) ? std::unique_ptr< T[] >( new T[ s ] ) : nullptr; capacity_ = s; } }
		size_t capacity() const { return capacity_; }

	private:
		size_t front_;
		size_t size_;

		size_t capacity_;
		std::unique_ptr< T[] > buffer_;
	};
}
