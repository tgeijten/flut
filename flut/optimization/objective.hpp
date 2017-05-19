#pragma once

#include "flut/system/types.hpp"
#include "flut/system/assert.hpp"
#include "par_set.hpp"
#include <functional>
#include "flut/math/bounds.hpp"

#if defined(_MSC_VER)
#	pragma warning( push )
#	pragma warning( disable: 4251 )
#endif

namespace flut
{
	using fitness_t = double;
	using fitness_vec_t = vector< fitness_t >;
	using par_mean_std = pair< par_value, par_value >;
	using par_bounds = bounds< par_value >;

	class FLUT_API objective
	{
	public:
		objective() {}
		virtual ~objective() {}

		virtual size_t dim() const = 0;
		virtual const vector< string >& parameter_names() const = 0;
		virtual const vector< par_bounds >& parameter_bounds() const = 0;
		virtual const vector< par_mean_std >& parameter_init() const = 0;

		virtual bool minimize() const { return true; }
		bool maximize() const { return !minimize(); }

		bool is_better( fitness_t a, fitness_t b ) const;
		fitness_t worst_fitness() const;

		virtual fitness_t evaluate( const par_vec& point ) const = 0;
	};

	class FLUT_API function_objective : public objective
	{ 
	public:
		typedef std::function< fitness_t( const par_vec& ) > function_t;

		function_objective( size_t d, function_t func, bool minimize = true, const vector< par_mean_std >& init = vector< par_mean_std >(), const vector< par_bounds >& b = vector< par_bounds >() );
		virtual size_t dim() const override { return dim_; }
		virtual const vector< par_bounds >& parameter_bounds() const override { return bounds_; }
		virtual const vector< par_mean_std >& parameter_init() const override { return init_; }
		virtual const vector< string >& parameter_names() const override { return names_; }

		virtual fitness_t evaluate( const par_vec& point ) const override { return func_( point ); }
		virtual bool minimize() const override { return minimize_; }

		size_t dim_;
		function_t func_;
		bool minimize_;
		vector< string > names_;
		vector< par_bounds > bounds_;
		vector< par_mean_std > init_;
	};
}

#if defined(_MSC_VER)
#	pragma warning( pop )
#endif
