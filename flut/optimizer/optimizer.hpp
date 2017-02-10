#pragma once

#include "flut/prop_node.hpp"
#include "flut/system/path.hpp"
#include "flut/system/types.hpp"
#include <functional>

#if defined(_MSC_VER)
#	pragma warning( push )
#	pragma warning( disable: 4251 )
#endif

namespace flut
{
	typedef std::function< double( const std::vector< double >& ) > objective_func_t;

	class FLUT_API optimizer
	{
	public:
		typedef vector< double > vec_double;

		static double no_objective_func( const vec_double& ) { flut_error( "No objective function" ); }

		optimizer( int dim, objective_func_t func = no_objective_func );
		virtual ~optimizer();

		virtual vec_double evaluate( const vector< vec_double >& pop );

		bool is_better( double a, double b ) { return maximize() ? a > b : a < b; }

		bool maximize() const { return maximize_; }
		void set_maximize( bool m ) { maximize_ = m; }
		
		int max_threads() const { return max_threads_; }
		void set_max_threads( int val ) { max_threads_ = val; }

	protected:

		// parameter settings
		bool maximize_ = false;
		int dim_ = -1;

		// evaluation settings
		int max_threads_ = 1;

		// objective
		objective_func_t func_;
	};
}

#if defined(_MSC_VER)
#	pragma warning( pop )
#endif
