#pragma once

#include "flut/system/types.hpp"
#include "flut/flat_map.hpp"
#include "flut/prop_node.hpp"
#include "par_info.hpp"

#if defined(_MSC_VER)
#	pragma warning( push )
#	pragma warning( disable: 4251 )
#endif

namespace flut
{
	class FLUT_API par_set
	{
	public:
		par_set( par_info& inf, const par_vec& values ) : info_( inf ), values_( values ) {}

		par_value get( const string& name, par_value mean, par_value std, par_value min, par_value max );
		par_value get( const string& name, const prop_node& prop );

	private:
		par_info& info_;
		const par_vec& values_;
		flat_map< string, par_value > fixed_param_values_;
	};
}

#if defined(_MSC_VER)
#	pragma warning( pop )
#endif
