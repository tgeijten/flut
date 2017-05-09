#pragma once

#include "flut/system/types.hpp"
#include "flut/flat_map.hpp"
#include "flut/prop_node.hpp"

#if defined(_MSC_VER)
#	pragma warning( push )
#	pragma warning( disable: 4251 )
#endif

namespace flut
{
	using param_t = double;
	using param_vec_t = vector< param_t >;

	class FLUT_API param_info
	{
	public:
		struct param
		{
			string name;
			param_t mean;
			param_t std;
			param_t min;
			param_t max;
		};

		size_t size() const { return params_.size(); }
		const vector< param >& get_params() const { return params_; }
		const param& operator[]( index_t i ) const { return params_[ i ]; }

		index_t add( const string& name, param_t mean, param_t std, param_t min, param_t max );


		index_t get_index( const string& name );
		index_t get_index( const string& name, param_t mean, param_t std, param_t min, param_t max );

		vector< param >::iterator find( const string& name );

		vector< param >::const_iterator begin() const { return params_.begin(); }
		vector< param >::const_iterator end() const { return params_.end(); }

		size_t import( const path& filename, bool import_std );
		void set_global_std( double factor, double offset );

	private:
		mutable std::vector< param > params_;
		bool under_construction_;
	};

	class FLUT_API param_set
	{
	public:
		param_set( param_info& inf ) : info_( inf ) {}

		param_t get( const string& name, param_t mean, param_t std, param_t min, param_t max );
		param_t get( const string& name, const prop_node& prop );

	private:
		param_info& info_;
		vector< param_t > values_;
		flat_map< string, param_t > fixed_param_values_;
	};
}

#if defined(_MSC_VER)
#	pragma warning( pop )
#endif
