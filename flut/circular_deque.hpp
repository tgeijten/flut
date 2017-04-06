#pragma once

#include "flut/dynarray.hpp"
#include "flut/system/assert.hpp"

namespace flut
{
	template< typename T >
	class circular_deque
	{
	public:
		circular_deque( size_t buf_size ) : data_( buf_size ), front_( 0 ), size_( 0 ) {}
		~circular_deque() {}

		void push_back( const T& value ) { flut_assert( size_ < buffer_size() ); ++size_; back() = value; }
		void push_front( const T& value ) { flut_assert( size_ < buffer_size() );  ++size_; front_ = ( front_ + buffer_size() - 1 ) % buffer_size(); front() = value; }

		void pop_back() { flut_assert( size_ > 0 ); --size_; }
		void pop_front() { flut_assert( size_ > 0 ); front_ = ( front_ + 1 ) % buffer_size(); --size_; }

		T& back() { flut_assert( size_ > 0 ); return data_[ ( front_ + size_ - 1 ) % buffer_size() ]; }
		const T& back() const { flut_assert( size_ > 0 ); return data_[ ( front_ + size_ ) % buffer_size() ]; }

		T& front() { flut_assert( size_ > 0 ); return data_[ front_ ]; }
		const T& front() const { flut_assert( size_ > 0 ); return data_[ front_ ]; }

		size_t size() const { return size_; }
		bool empty() const { return size_ == 0; }
		void clear() { front_ = size_ = 0; }
		size_t buffer_size() const { return data_.size(); }

	private:
		size_t front_;
		size_t size_;
		dynarray< T > data_;
	};
}
