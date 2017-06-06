#pragma once

#include <limits>
#include <type_traits>

namespace flut
{
	template< typename T, typename E = void > struct optional_pod;

	template< typename T > struct optional_pod< T, typename std::enable_if< std::is_integral<T>::value >::type >
	{
		optional_pod() : value( math::numeric_const<T>::rare() ) {}
		optional_pod( const T& v ) : value( v ) {}
		operator bool() const { return value != math::numeric_const<T>::rare(); }
		T& operator*() { return value; }
		const T& operator*() const { return value; }
		T value;
	};

	template< typename T > struct optional_pod< T, typename std::enable_if< std::is_floating_point<T>::value >::type >
	{
		optional_pod() : value( std::numeric_limits<T>::quiet_NaN() ) {}
		optional_pod( const T& v ) : value( v ) {}
		operator bool() { return value == value; }
		T& operator*() { return value; }
		const T& operator*() const { return value; }
		T value;
	};

	using optional_int = optional_pod< int >;
	using optional_size = optional_pod< size_t >;
	using optional_float = optional_pod< float >;
	using optional_double = optional_pod< double >;
}
