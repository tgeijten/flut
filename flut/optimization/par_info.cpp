#include "par_info.hpp"

#include "flut/container_tools.hpp"
#include "flut/system/assert.hpp"
#include <fstream>

namespace flut
{
	flut::index_t par_info::add( const string& name, par_value mean, par_value std, par_value min, par_value max )
	{
		params_.emplace_back( parameter{ name, mean, std, min, max } );
		return params_.size() - 1;
	}

	flut::index_t par_info::get_index( const string& name )
	{
		auto it = find( name );
		return ( it != params_.end() ) ? it - params_.begin() : no_index;
	}

	flut::index_t par_info::get_index( const string& name, par_value mean, par_value std, par_value min, par_value max )
	{
		auto idx = get_index( name );
		if ( idx != no_index )
			return idx;
		else if ( under_construction_ )
			return add( name, mean, std, min, max );
		else return no_index;
	}

	vector< flut::par_info::parameter >::iterator par_info::find( const string& name )
	{
		return find_if( params_, [&]( parameter& p ) { return p.name == name; } );
	}

	size_t par_info::import( const path& filename, bool import_std )
	{
		size_t params_set = 0;
		size_t params_not_found = 0;

		std::ifstream str( filename.str() );
		flut_error_if( !str.good(), "Error opening file: " + filename.str() );
		while ( str.good() )
		{
			std::string name;
			double value, mean, std;
			str >> name >> value >> mean >> std;

			auto iter = find( name );
			if ( iter != end() )
			{
				// read existing parameter, updating mean / std
				iter->mean = mean;
				if ( import_std )
					iter->std = std;
				++params_set;
			}
			else ++params_not_found;
		}
		return params_set;
	}

	void par_info::set_global_std( double factor, double offset )
	{
		for ( auto& p : params_ )
			p.std = factor * fabs( p.mean ) + offset;
	}
}
