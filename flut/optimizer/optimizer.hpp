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
		typedef vector< double > real_vec;

		optimizer( int dim );
		optimizer( int dim, const real_vec& lower, const real_vec& upper );
		virtual ~optimizer();

		//virtual real_vec evaluate( const vector< real_vec >& pop );
		bool is_better( double a, double b ) { return maximize ? a > b : a < b; }
		
	protected:
		void to_bounded( real_vec& values );
		void from_bounded( real_vec& values );

		// parameter settings
		bool maximize = false;
		int dim = -1;

		// evaluation settings
		int max_threads = 1;

		// objective
		//objective_func_t func;

		// boundaries
		real_vec lower_bounds;
		real_vec upper_bounds;
	};
}

#if defined(_MSC_VER)
#	pragma warning( pop )
#endif
