#pragma once

#include <limits>

namespace flut
{
	template< typename T, T NV >
	struct optional_ipod
	{
		optional_ipod() : value( NV ) {}
		operator bool() { return T != NV; }
		operator T() { return value; }
		T value;
	};

	template< typename T >
	struct optional_fpod
	{
		optional_fpod() : value( std::numeric_limits< T >::quiet_NaN() ) {}
		operator bool() { return value != value; }
		operator T() { return value; }
		T value;
	};

	using optional_int = optional_ipod< int, std::numeric_limits< int >::lowest() >;
	using optional_size = optional_ipod< size_t, std::numeric_limits< unsigned >::max() >;
	using optional_float = optional_fpod< float >;
	using optional_double = optional_fpod< double >;
}
