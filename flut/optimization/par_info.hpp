#pragma once

#include "flut/system/platform.hpp"
#include "flut/system/types.hpp"
#include "flut/flat_map.hpp"
#include "flut/system/path.hpp"

#if defined(_MSC_VER)
#	pragma warning( push )
#	pragma warning( disable: 4251 )
#endif

namespace flut
{
	using par_value = double;
	using par_vec = vector< par_value >;

	class FLUT_API par_info
	{
	public:
		struct parameter
		{
			string name;
			par_value mean;
			par_value std;
			par_value min;
			par_value max;
		};

		size_t size() const { return params_.size(); }
		const vector< parameter >& get_params() const { return params_; }
		const parameter& operator[]( index_t i ) const { return params_[ i ]; }

		index_t add( const string& name, par_value mean, par_value std, par_value min, par_value max );

		index_t get_index( const string& name );
		index_t get_index( const string& name, par_value mean, par_value std, par_value min, par_value max );

		vector< parameter >::iterator find( const string& name );

		vector< parameter >::const_iterator begin() const { return params_.begin(); }
		vector< parameter >::const_iterator end() const { return params_.end(); }

		size_t import( const path& filename, bool import_std );
		void set_global_std( double factor, double offset );

	private:
		mutable std::vector< parameter > params_;
		bool under_construction_;
	};
}

#if defined(_MSC_VER)
#	pragma warning( pop )
#endif
