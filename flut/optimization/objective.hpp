#pragma once

#include "flut/system/types.hpp"
#include "flut/system/assert.hpp"
#include "par_set.hpp"
#include <functional>

#if defined(_MSC_VER)
#	pragma warning( push )
#	pragma warning( disable: 4251 )
#endif

namespace flut
{
	using fitness_t = double;
	using fitness_vec_t = vector< fitness_t >;

	class FLUT_API objective
	{
	public:
		objective() {}
		virtual ~objective() {}

		virtual size_t dim() const { return param_info_.size(); }
		const par_info& info() const { return param_info_; }
		par_info& info() { return param_info_; }

		virtual bool minimize() const { return true; }
		bool maximize() const { return !minimize(); }

		bool is_better( fitness_t a, fitness_t b ) const;
		fitness_t worst_fitness() const;

		virtual fitness_t evaluate( const par_vec& point ) const = 0;

	protected:
		par_info param_info_;
	};

	class FLUT_API function_objective : public objective
	{
	public:
		typedef std::function< fitness_t( const par_vec& ) > function_t;

		function_objective( size_t d, function_t func, bool minimize = true,
			const par_vec& start = par_vec(), const par_vec& start_std = par_vec(),
			const par_vec& upper = par_vec(), const par_vec& lower = par_vec() );

		virtual fitness_t evaluate( const par_vec& point ) const override { return func_( point ); }
		virtual bool minimize() const override { return minimize_; }

		function_t func_;
		bool minimize_ = true;
	};
}

#if defined(_MSC_VER)
#	pragma warning( pop )
#endif
