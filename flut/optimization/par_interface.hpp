#pragma once

#include "flut/string_tools.hpp"
#include "flut/prop_node.hpp"
#include "flut/math/optional_pod.hpp"

namespace flut
{
	using par_value = double;
	using optional_par_value = optional_double;

	class FLUT_API par_interface
	{
	public:
		par_interface() {}
		virtual ~par_interface() {}

		virtual optional_par_value get( const string& name ) = 0;
		virtual par_value add( const string& name, par_value mean, par_value std, par_value min = -1e15, par_value max = 1e15 ) = 0;

		par_value get( const string& name, par_value mean, par_value std, par_value min = -1e15, par_value max = 1e15 );
		par_value get( const string& name, const prop_node& prop );

	protected:
	private:
	};
}
