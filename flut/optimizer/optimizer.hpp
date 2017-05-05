#pragma once

#include "flut/prop_node.hpp"
#include "flut/system/path.hpp"
#include "flut/system/types.hpp"
#include <functional>
#include "objective.hpp"

#if defined(_MSC_VER)
#	pragma warning( push )
#	pragma warning( disable: 4251 )
#endif

namespace flut
{
	class FLUT_API optimizer
	{
	public:
		optimizer( const objective& o = no_objective_ );
		virtual ~optimizer();

		virtual fitness_vec_t evaluate( const vector< param_vec_t >& pop );
		
		int max_threads() const { return max_threads_; }
		void set_max_threads( int val ) { max_threads_ = val; }

		struct generation_result {
			float best;
			float median;
			float average;
		};

		const vector< generation_result >& history() { return history_; }

	protected:

		// evaluation settings
		int max_threads_ = 1;

		vector< generation_result > history_;

		// objective
		const objective& objective_;

	private:
		static no_objective no_objective_;
	};
}

#if defined(_MSC_VER)
#	pragma warning( pop )
#endif
