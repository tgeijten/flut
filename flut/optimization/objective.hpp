#pragma once

#include "flut/system/types.hpp"
#include "flut/system/assert.hpp"

namespace flut
{
	typedef double param_t;
	typedef double fitness_t;
	typedef vector< param_t > param_vec_t;
	typedef vector< fitness_t > fitness_vec_t;

	class objective
	{
	public:
		objective() {}
		virtual ~objective() {}

		virtual size_t dim() const = 0;

		virtual param_vec_t starting_point() const { return param_vec_t( dim(), 0.0 ); }
		virtual param_vec_t starting_point_std() const { return param_vec_t( dim(), 1.0 ); }

		virtual param_vec_t upper_bounds() const { return param_vec_t( dim(), 1e15 ); }
		virtual param_vec_t lower_bounds() const { return param_vec_t( dim(), -1e15 ); }

		virtual bool minimize() const { return true; }
		bool maximize() const { return !minimize(); }
		bool is_better( fitness_t a, fitness_t b ) const { return minimize() ? a < b : a > b; }
		fitness_t worst_fitness() const { return minimize() ? std::numeric_limits< fitness_t >::max() : std::numeric_limits< fitness_t >::lowest(); }

		virtual fitness_t evaluate( const param_vec_t& point ) const = 0;
	};

	class function_objective : public objective
	{
	public:
		typedef std::function< fitness_t( const param_vec_t& ) > function_t;

		function_objective( size_t d, function_t func,
			const param_vec_t& start = param_vec_t(), const param_vec_t& start_std = param_vec_t(),
			const param_vec_t& upper = param_vec_t(), const param_vec_t& lower = param_vec_t() ) :
			dim_( d ), func_( func ),
			starting_point_( !start.empty() ? start : param_vec_t( d, 0.0 ) ),
			starting_point_std_( !start_std.empty() ? start_std : param_vec_t( d, 1.0 ) ),
			upper_bounds_( upper ),
			lower_bounds_( lower ) {}

		virtual size_t dim() const override { return dim_; }
		virtual fitness_t evaluate( const param_vec_t& point ) const override { return func_( point ); }
		virtual param_vec_t upper_bounds() const override { return upper_bounds_; }
		virtual param_vec_t lower_bounds() const override { return lower_bounds_; }
		virtual bool minimize() const override { return minimize_; }
		virtual param_vec_t starting_point() const override { return starting_point_; }
		virtual param_vec_t starting_point_std() const override { return starting_point_std_; }

		size_t dim_;
		function_t func_;
		param_vec_t starting_point_;
		param_vec_t starting_point_std_;
		param_vec_t upper_bounds_;
		param_vec_t lower_bounds_;
		bool minimize_ = true;
	};
}
