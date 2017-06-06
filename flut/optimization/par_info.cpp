#include "par_info.hpp"

#include "flut/container_tools.hpp"
#include "flut/system/assert.hpp"
#include <fstream>

namespace flut
{
	optional_par_value par_info::try_get( const string& name ) const
	{
		auto it = find( name );
		if ( it != params_.end() )
			return it->mean;
		else return try_get_fixed( name );
	}

	flut::optional_par_value par_info::try_get_fixed( const string& name ) const
	{
		auto it = fixed_values_.find( name );
		if ( it != fixed_values_.end() )
			return it->second;
		else return optional_par_value();
	}

	par_value par_info::add( const string& name, par_value mean, par_value std, par_value min, par_value max )
	{
		flut_assert( find( name ) == params_.end() );
		params_.emplace_back( parameter{ name, mean, std, min, max } );
		return params_.back().mean;
	}

	par_info::par_info_vec::iterator par_info::find( const string& name ) const
	{
		return find_if( params_, [&]( parameter& p ) { return p.name == name; } );
	}

	index_t par_info::find_index( const string& name ) const
	{
		return get_index( find( name ) );
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

	size_t par_info::import_fixed( const path& filename )
	{
		fixed_values_.clear();

		flut::char_stream str( filename );
		while ( str.good() )
		{
			string name;
			double value, mean, std;
			str >> name >> value >> mean >> std;
			if ( !str.fail() )
			{
				if ( find( name ) == params_.end() )
					fixed_values_[ name ] = value;
			}
		}
		return fixed_values_.size();
	}

	void par_info::set_global_std( double factor, double offset )
	{
		for ( auto& p : params_ )
			p.std = factor * fabs( p.mean ) + offset;
	}

	void par_info::set_mean_std( const vector< par_value >& mean, const vector< par_value >& std )
	{
		flut_assert( mean.size() == size() && std.size() == size() );
		for ( index_t i = 0; i < size(); ++i )
		{
			params_[ i ].mean = mean[ i ];
			params_[ i ].std = std[ i ];
		}
	}

	const flut::par_info& par_info::empty_instance()
	{
		static const par_info empty_par_info;
		return empty_par_info;
	}
}
