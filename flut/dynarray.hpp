#pragma once

#include <memory>
#include <algorithm>

namespace flut
{
	template< typename T >
	class dynarray
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;

		dynarray( size_t n ) : data_( new T[ n ] ), end_( data_.get() + n ) {}
		dynarray( size_t n, const T& v ) : data_( new T[ n ] ), end_( data_.get() + n ) { assign( v ); }
		~dynarray() {}

		T& operator[]( size_t i ) { return data_[ i ]; }
		const T& operator[]( size_t i ) const { return data_[ i ]; }

		T& at( size_t i ) { flut_error_if( i >= size_, "dynarray index out of bounds" ); return data_[ i ]; }
		const T& at( size_t i ) const { flut_error_if( i >= size_, "dynarray index out of bounds" ); return data_[ i ]; }

		T* begin() { return data_.get(); }
		const T* begin() const { return data_.get(); }
		const T* cbegin() const { return data_.get(); }

		T* end() { return end_; }
		const T* end() const { return end_; }
		const T* cend() const { return end_; }

		size_t size() const { return end() - begin(); }

		void assign( const T& v ) { std::fill( begin(), end(), v ); }

		T* data() { return data_.get(); }
		const T* data() const { return data_.get(); }

	private:
		std::unique_ptr< T[] > data_;
		T* end_;
	};
}
