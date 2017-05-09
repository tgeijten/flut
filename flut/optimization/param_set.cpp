#include "param_set.hpp"

#include "flut/container_tools.hpp"
#include <fstream>

namespace flut
{

	flut::index_t param_info::add( const string& name, param_t mean, param_t std, param_t min, param_t max )
	{
		params_.emplace_back( param{ name, mean, std, min, max } );
		return params_.size() - 1;
	}

	flut::index_t param_info::get_index( const string& name )
	{
		auto it = find( name );
		return ( it != params_.end() ) ? it - params_.begin() : no_index;
	}

	flut::index_t param_info::get_index( const string& name, param_t mean, param_t std, param_t min, param_t max )
	{
		auto idx = get_index( name );
		if ( idx != no_index )
			return idx;
		else if ( under_construction_ )
			return add( name, mean, std, min, max );
		else return no_index;
	}

	vector< flut::param_info::param >::iterator param_info::find( const string& name )
	{
		return find_if( params_, [&]( param& p ) { return p.name == name; } );
	}

	size_t param_info::import( const path& filename, bool import_std )
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

	void param_info::set_global_std( double factor, double offset )
	{
		for ( auto& p : params_ )
			p.std = factor * fabs( p.mean ) + offset;
	}

	param_t param_set::get( const string& name, param_t mean, param_t std, param_t min, param_t max )
	{
		auto idx = info_.get_index( name, mean, std, min, max );
		if ( idx < values_.size() )
			return values_[ idx ];
		else return mean;
	}

	param_t param_set::get( const string& name, const prop_node& prop )
	{
		return 0.0;
	}
}
