#pragma once

#include <array>
#include <initializer_list>

namespace flut
{
	template< typename T, size_t D >
	struct polynomial
	{
		polynomial() { static_assert( D > 0, "polynomial degree must be > 0" ); }
		template<typename ...E> polynomial( E&&...e ) : coeff{ { std::forward<E>( e )... } } {}

		T operator()( const T& v ) const {
			T result = coeff[ 0 ];
			T factor = T( v );
			for ( auto it = std::begin( coeff ) + 1; it != std::end( coeff ); ++it ) { result += factor * *it; factor *= v; }
			return result;
		}
		std::array< T, D + 1 > coeff;
	};

	template< typename T > using linear_function = polynomial< T, 1 >;
	template< typename T > using quadratic_function = polynomial< T, 2 >;
	template< typename T > using cubic_function = polynomial< T, 3 >;

	template< typename T > T solve_x( const linear_function< T >& f, T x ) { return ( f.coeff[ 0 ] - x ) / -f.coeff[ 1 ]; }
}
