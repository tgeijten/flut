#pragma once

#define flut_result_type( A_, B_ ) decltype( A_(1) + B(1) )

namespace flut
{
	/// result types
	template< typename A, typename B > struct result_type { typedef decltype( A(1) + B(1) ) type; };
}
