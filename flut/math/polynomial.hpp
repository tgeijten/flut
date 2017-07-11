#pragma once

#include <array>
#include <initializer_list>

namespace flut
{
	namespace math
	{
		template< typename T, int D >
		struct polynomial
		{
			polynomial() { static_assert( D > 0 ); }
			polynomial( std::initializer_list< T > coefficients ) : coeff( coefficients ) { static_assert( D > 0 ); }
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
	}
}
