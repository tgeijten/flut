#pragma once

#include "../types.hpp"
#include <limits>

namespace flut
{
	namespace math
	{
		// TODO: use constexpr when VS allows it
		template< typename T >
		struct constants
		{
			static const T pi() { return T( 3.14159265358979 ); }
			static const T half_pi() { return T( 0.5 * 3.14159265358979 ); }
			static const T two_pi() { return T( 2.0 * 3.14159265358979 ); }
			static const T epsilon() { return std::numeric_limits< T >::epsilon(); }
			static const T one() { return T( 1 ); }
			static const T zero() { return T( 0 ); }
		};

		template< typename T > T rad_to_deg( T rad_value ) { return ( T( 180 ) / constants<T>::pi() ) * rad_value; }
		template< typename T > T deg_to_rad( T deg_value ) { return ( constants<T>::pi() / T( 180 ) ) * deg_value; }

		struct radian;
		struct degree;

		struct radian
		{
			explicit radian( real_t v = 0.0 ) : value( v ) {}
			radian( degree v );
			real_t value;
		};
		struct degree
		{
			explicit degree( real_t v = 0.0 ) : value( v ) {}
			degree( const radian& v ) : value( rad_to_deg( v.value ) ) {}
			real_t value;
		};
		radian::radian( degree v ) : value( deg_to_rad( v.value ) ) {}

		enum class euler_order
		{
			xyz,
			xzy,
			yxz,
			yzx,
			zxy,
			zyx
		};
	}
}
