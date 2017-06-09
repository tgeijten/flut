#pragma once

#include "flut/system/types.hpp"
#include "flut/flat_map.hpp"
#include "flut/prop_node.hpp"
#include "objective_info.hpp"
#include "par_io.hpp"

#if defined(_MSC_VER)
#	pragma warning( push )
#	pragma warning( disable: 4251 )
#endif

namespace flut
{
	class FLUT_API search_point : public par_io
	{
	public:
		search_point( const objective_info& inf );
		search_point( const objective_info& inf, const par_vec& values );
		search_point( const objective_info& inf, par_vec&& values );
		search_point( const objective_info& inf, const path& filename );

		virtual size_t dim() const override { return info_.dim(); }
		virtual optional_par_value try_get( const string& full_name ) const override;
		virtual par_value add( const string& name, par_value mean, par_value std, par_value min, par_value max ) override;

		const par_value& operator[]( index_t i ) const { return values_[ i ]; }
		using par_io::get;

		const objective_info& info() const { return info_; }
		size_t size() const { return info_.size(); }
		size_t import_values( const path& filename );

		friend FLUT_API std::ostream& operator<<( std::ostream& str, const search_point& ps );

		void round_values();
		const par_vec& values() const { return values_; }

	private:
		par_value rounded( par_value );

		const objective_info& info_;
		par_vec values_;
	};
}

#if defined(_MSC_VER)
#	pragma warning( pop )
#endif
