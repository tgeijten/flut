#pragma once

#include "flut/system/platform.hpp"
#include "flut/system/types.hpp"
#include "flut/flat_map.hpp"
#include "flut/system/path.hpp"
#include "par_interface.hpp"

#if defined(_MSC_VER)
#	pragma warning( push )
#	pragma warning( disable: 4251 )
#endif

namespace flut
{
	using par_value = double;
	using par_vec = vector< par_value >;

	class FLUT_API par_info : public par_interface
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

		using par_info_vec = vector< parameter >;

		par_info() {}

		virtual par_value add( const string& name, par_value mean, par_value std, par_value min = -1e15, par_value max = 1e15 ) override;
		virtual optional_par_value try_get( const string& name ) const override;
		optional_par_value try_get_fixed( const string& name ) const;

		/// access by index
		const parameter& operator[]( index_t i ) const { return params_[ i ]; }

		/// access by name
		par_info_vec::iterator find( const string& name ) const;
		index_t find_index( const string& name ) const;

		/// iterator access
		par_info_vec::const_iterator begin() const { return params_.begin(); }
		par_info_vec::const_iterator end() const { return params_.end(); }

		/// properties
		size_t size() const { return params_.size(); }
		bool empty() const { return params_.empty(); }

		/// import / export
		size_t import( const path& filename, bool import_std );
		size_t import_fixed( const path& filename );
		void set_global_std( double factor, double offset );
		void set_mean_std( const vector< par_value >& mean, const vector< par_value >& std );

		/// static empty member
		const static par_info& empty_instance();
		index_t get_index( par_info_vec::iterator it ) const { return it != params_.end() ? it - params_.begin() : no_index; }

	private:
		mutable par_info_vec params_;
		flat_map< string, par_value > fixed_values_;
	};
}

#if defined(_MSC_VER)
#	pragma warning( pop )
#endif
