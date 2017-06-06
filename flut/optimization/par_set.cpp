#include "par_set.hpp"

#include "flut/container_tools.hpp"
#include <fstream>

namespace flut
{
	par_set::par_set( const par_info& inf, par_vec values ) : info_( inf ), values_( values )
	{
		if ( values_.empty() )
		{
			// init with default values
			values_.reserve( info_.size() );
			for ( auto& p : info_ )
				values_.push_back( p.mean );
		}
		round_values();

		flut_assert( info_.size() == values_.size() );
	}

	optional_par_value par_set::try_get( const string& full_name ) const
	{
		// see if this is a parameter
		auto idx = info_.find_index( full_name );
		if ( idx != no_index )
			return values_[ idx ];
		else return info_.try_get_fixed( full_name );
	}

	par_value par_set::add( const string& full_name, par_value mean, par_value std, par_value min, par_value max )
	{
		flut_error( "Cannot add parameter" );
	}

	void par_set::round_values()
	{
		for ( auto& v : values_ )
			v = rounded( v );
	}

	flut::par_value par_set::rounded( par_value v )
	{
		std::stringstream str;
		str << std::setprecision( 8 ) << v;
		str >> v;
		return v;
	}

	std::ostream& operator<<( std::ostream& str, const par_set& ps )
	{
		for ( index_t idx = 0; idx < ps.size(); ++idx )
		{
			auto& inf = ps.info()[ idx ];
			str << std::left << std::setw( 20 ) << inf.name << "\t";
			str << std::setprecision( 8 ) << ps.get( idx ) << "\t" << inf.mean << "\t" << inf.std << "\t" << std::endl;
		}
		return str;
	}
}
