#pragma once

#include "flut/system/types.hpp"
#include "flut/system/assert.hpp"
#include "param_set.hpp"
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
		const param_info& info() const { return param_info_; }
		param_info& info() { return param_info_; }

		virtual bool minimize() const { return true; }
		bool maximize() const { return !minimize(); }

		bool is_better( fitness_t a, fitness_t b ) const;
		fitness_t worst_fitness() const;

		virtual fitness_t evaluate( const param_vec_t& point ) const = 0;

	protected:
		param_info param_info_;
	};

	class FLUT_API function_objective : public objective
	{
	public:
		typedef std::function< fitness_t( const param_vec_t& ) > function_t;

		function_objective( size_t d, function_t func, bool minimize = true,
			const param_vec_t& start = param_vec_t(), const param_vec_t& start_std = param_vec_t(),
			const param_vec_t& upper = param_vec_t(), const param_vec_t& lower = param_vec_t() );

		virtual fitness_t evaluate( const param_vec_t& point ) const override { return func_( point ); }
		virtual bool minimize() const override { return minimize_; }

		function_t func_;
		bool minimize_ = true;
	};
}

#if defined(_MSC_VER)
#	pragma warning( pop )
#endif
