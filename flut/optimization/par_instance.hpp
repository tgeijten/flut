#pragma once

#include "flut/system/types.hpp"
#include "flut/flat_map.hpp"
#include "flut/prop_node.hpp"
#include "par_info.hpp"
#include "par_interface.hpp"

#if defined(_MSC_VER)
#	pragma warning( push )
#	pragma warning( disable: 4251 )
#endif

namespace flut
{
	class FLUT_API par_instance : public par_interface
	{
	public:
		par_instance( const par_info& inf );
		par_instance( const par_info& inf, par_vec values );
		par_instance( const par_info& inf, const path& filename );

		virtual size_t dim() const override { return info_.dim(); }
		virtual optional_par_value try_get( const string& full_name ) const override;
		virtual par_value add( const string& name, par_value mean, par_value std, par_value min, par_value max ) override;

		par_value get( index_t i ) const { return values_[ i ]; }
		using par_interface::get;

		const par_info& info() const { return info_; }
		size_t size() const { return info_.size(); }
		size_t import_values( const path& filename );

		friend FLUT_API std::ostream& operator<<( std::ostream& str, const par_instance& ps );

		void round_values();
		const par_vec& values() const { return values_; }

	private:
		par_value rounded( par_value );

		const par_info& info_;
		par_vec values_;
	};
}

#if defined(_MSC_VER)
#	pragma warning( pop )
#endif
