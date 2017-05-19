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

		using par_info_vec = vector< parameter >;

		par_info( bool under_construction = true ) : under_construction_( under_construction ) {}

		/// access by index
		const parameter& operator[]( index_t i ) const { return params_[ i ]; }

		/// access by name
		par_info_vec::iterator find( const string& name ) const;
		index_t find_index( const string& name ) const;

		/// add entry
		void push_back( const string& name, par_value mean, par_value std, par_value min, par_value max ) const;
		par_info_vec::iterator acquire( const string& name, par_value mean, par_value std, par_value min, par_value max ) const;
		index_t acquire_index( const string& name, par_value mean, par_value std, par_value min, par_value max ) const;

		/// iterator access
		par_info_vec::const_iterator begin() const { return params_.begin(); }
		par_info_vec::const_iterator end() const { return params_.end(); }

		/// properties
		size_t size() const { return params_.size(); }
		bool empty() const { return params_.empty(); }

		/// import / export
		size_t import( const path& filename, bool import_std );
		void set_global_std( double factor, double offset );
		void set_mean_std( const vector< par_value >& mean, const vector< par_value >& std );

		/// static empty member
		const static par_info& empty_instance();
		index_t get_index( par_info_vec::iterator it ) const { return it != params_.end() ? it - params_.begin() : no_index; }

		bool finalized() const { return !under_construction_; }
		void finalize() { under_construction_ = false; }

	private:
		mutable par_info_vec params_;
		bool under_construction_;
	};
}

#if defined(_MSC_VER)
#	pragma warning( pop )
#endif
