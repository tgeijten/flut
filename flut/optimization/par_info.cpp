#include "par_info.hpp"

#include "flut/container_tools.hpp"
#include "flut/system/assert.hpp"
#include <fstream>

namespace flut
{
	par_info_set::par_info_vec::iterator par_info_set::find( const string& name ) const
	{
		return find_if( params_, [&]( par_info& p ) { return p.name == name; } );
	}

	index_t par_info_set::find_index( const string& name ) const
	{
		return get_index( find( name ) );
	}

	void par_info_set::push_back( const string& name, par_value mean, par_value std, par_value min, par_value max ) const
	{
		flut_error_if( finalized(), "Cannot add parameter after par_info has been finalized" );
		params_.emplace_back( par_info{ name, mean, std, min, max } );
	}

	par_info_set::par_info_vec::iterator par_info_set::acquire( const string& name, par_value mean, par_value std, par_value min, par_value max ) const
	{
		auto it = find( name );
		if ( it == params_.end() )
		{
			push_back( name, mean, std, min, max );
			return params_.end() - 1;
		}
		else return it;
	}

	index_t par_info_set::acquire_index( const string& name, par_value mean, par_value std, par_value min, par_value max ) const
	{
		return get_index( acquire( name, mean, std, min, max ) );
	}

	size_t par_info_set::import( const path& filename, bool import_std )
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

	void par_info_set::set_global_std( double factor, double offset )
	{
		for ( auto& p : params_ )
			p.std = factor * fabs( p.mean ) + offset;
	}

	const flut::par_info_set& par_info_set::empty_instance()
	{
		static const par_info_set empty_par_info( false );
		return empty_par_info;
	}
}
