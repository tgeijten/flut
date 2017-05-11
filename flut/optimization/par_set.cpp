#include "par_set.hpp"

#include "flut/container_tools.hpp"
#include <fstream>

namespace flut
{
	par_value par_set::get( const string& name, par_value mean, par_value std, par_value min, par_value max )
	{
		auto idx = info_.get_index( name, mean, std, min, max );
		if ( idx < values_.size() )
			return values_[ idx ];
		else return mean;
	}

	par_value par_set::get( const string& name, const prop_node& prop )
	{
		return 0.0;
	}
}
