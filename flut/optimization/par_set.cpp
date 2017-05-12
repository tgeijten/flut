#include "par_set.hpp"

#include "flut/container_tools.hpp"
#include <fstream>

namespace flut
{
	par_set::par_set( const par_info_set& inf, par_vec values ) : info_( inf ), values_( values )
	{
		if ( values_.empty() )
		{
			// init with default values
			values_.reserve( info_.size() );
			for ( auto& p : info_ )
				values_.push_back( p.mean );
		}

		flut_assert( info_.size() == values_.size() );
	}

	flut::par_value* par_set::try_get( const string& full_name )
	{
		// see if this is a parameter
		auto idx = info_.find_index( full_name );
		if ( idx != no_index )
			return &values_[ idx ];

		// see if it's a fixed variable
		auto it = fixed_values_.find( full_name );
		if ( it != fixed_values_.end() )
			return &it->second;

		return nullptr;
	}

	par_value par_set::try_add( const string& full_name, par_value mean, par_value std, par_value min, par_value max )
	{
		if ( !info_.finalized() )
		{
			info_.push_back( full_name, mean, std, min, max );
			values_.push_back( mean );
			return values_.back();
		}
		else return mean;
	}

	par_value par_set::get( const string& name, par_value mean, par_value std, par_value min, par_value max )
	{
		auto full_name = prefix() + name;

		// check if we already have a value for this name
		if ( auto* v = try_get( full_name ) )
			return *v;

		// make a new parameter if we are allowed to
		return try_add( full_name, mean, std, min, max );
	}

	par_value par_set::get( const string& name, const prop_node& pn )
	{
		auto full_name = prefix() + name;

		// check if we already have a value for this name
		if ( auto* val = try_get( full_name ) )
			return *val;

		// interpret the struct
		auto vec = str_to_vec< par_value >( pn.get_value(), 4, " \t," );
		if ( vec.empty() )
		{
			// add new param
			return try_add( full_name,
				pn.get_any< par_value >( { "mean", "init_mean" } ),
				pn.get_any< par_value >( { "std", "init_std" } ),
				pn.get< par_value >( "min", -1e18 ),
				pn.get< par_value >( "max", 1e18 ) );
		}
		else if ( vec.size() == 1 )
		{
			// we have only a value
			return vec[ 0 ];
		}
		else
		{
			return try_add( full_name, vec[ 0 ], vec[ 1 ], vec.size() > 2 ? vec[ 2 ] : -1e18, vec.size() > 3 ? vec[ 3 ] : 1e18 );
		}
	}

	void par_set::set_value( const string& name, par_value value )
	{
		auto idx = info_.find_index( name );
		if ( idx != no_index )
			values_[ idx ] = value;
		else fixed_values_[ name ] = value;
	}

	std::istream& operator>>( std::istream& str, par_set& ps )
	{
		while ( str.good() )
		{
			string name;
			double value, mean, std;
			str >> name >> value >> mean >> std;
			if ( !str.fail() )
				ps.set_value( name, value );
		}

		return str;
	}

	std::ostream& operator<<( std::ostream& str, const par_set& ps )
	{
		for ( index_t idx = 0; idx < ps.size(); ++idx )
		{
			auto& inf = ps.info()[ idx ];
			str << std::left << std::setw( 20 ) << inf.name << "\t";
			str << std::setprecision( 8 ) << ps[ idx ] << "\t" << inf.mean << "\t" << inf.std << "\t" << std::endl;
		}
		return str;
	}
}
