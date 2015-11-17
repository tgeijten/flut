#pragma once

#define flut_result( A_, B_ ) typename ::flut::math::result< A_, B_ >::type

namespace flut
{
	namespace math
	{
		/// result types
		template< typename A, typename B > struct result { typedef decltype( A(1) + B(1) ) type; };
	}
}
