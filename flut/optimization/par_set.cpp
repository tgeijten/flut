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

	void par_set::set_value( const string& name, par_value value )
	{
		auto idx = info().get_index( name );
		if ( idx != no_index )
			values_[ idx ] = value;
		else fixed_values_[ name ] = value;
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

	std::istream& operator>>( std::istream& str, par_set& ps )
	{
		while ( str.good() )
		{
			string name;
			double value;
			str >> name >> value;
			if ( !str.fail() )
				ps.set_value( name, value );
		}

		return str;
	}
}
