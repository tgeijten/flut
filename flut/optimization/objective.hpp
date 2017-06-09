#pragma once

#include "flut/system/types.hpp"
#include "flut/system/assert.hpp"
#include "search_point.hpp"
#include <functional>

#if defined(_MSC_VER)
#	pragma warning( push )
#	pragma warning( disable: 4251 )
#endif

namespace flut
{
	class FLUT_API objective
	{
	public:
		objective() {}
		virtual ~objective() {}

		const objective_info& info() const { return info_; }
		objective_info& info() { return info_; }
		size_t dim() const { return info_.dim(); }

		virtual fitness_t evaluate( const par_vec& point ) const = 0;

	protected:
		objective_info info_;
	};

	class FLUT_API function_objective : public objective
	{
	public:
		typedef std::function< fitness_t( const par_vec& ) > function_t;

		function_objective( size_t d, function_t func, bool minimize = true,
			const par_vec& start = par_vec(), const par_vec& start_std = par_vec(),
			const par_vec& upper = par_vec(), const par_vec& lower = par_vec() );

		virtual fitness_t evaluate( const par_vec& point ) const override { return func_( point ); }

		function_t func_;
	};
}

#if defined(_MSC_VER)
#	pragma warning( pop )
#endif
