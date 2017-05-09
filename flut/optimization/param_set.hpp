#pragma once

#include "flut/system/types.hpp"
#include "flut/flat_map.hpp"
#include "flut/prop_node.hpp"

namespace flut
{
	class param_info
	{
	public:
		struct param
		{
			string name;
			double mean;
			double std;
			double min;
			double max;
		};

		index_t acquire( const string& name, double mean, double std, double min, double max );
		index_t acquire( const string& name, const prop_node& prop );

	private:
		mutable std::vector< param > param_infos_;
		bool under_construction_;
	};

	class param_set
	{
	public:
		param_set( const param_info& inf ) : info_( inf ) {}

		double get( const string& name, double mean, double std, double min, double max );
		double get( const string& name, const prop_node& prop );

	private:
		const param_info& info_;
		vector< double > params_;

		flat_map< string, double > fixed_param_values_;
	};
}
