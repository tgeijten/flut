#pragma once

#include "flut/prop_node.hpp"
#include "flut/system/path.hpp"
#include "flut/system/types.hpp"
#include <functional>
#include "objective.hpp"
#include "flut/math/math.hpp"
#include <atomic>

#if defined(_MSC_VER)
#	pragma warning( push )
#	pragma warning( disable: 4251 )
#endif

namespace flut
{
	class FLUT_API optimizer
	{
	public:
		struct stop_condition
		{
			size_t max_generations = 10000;
			size_t progress_window_size = 0;
			fitness_t min_progress = 0;
			fitness_t fitness = math::num_const_d::nan();
		};

		struct fitness_report {
			fitness_t best = 0.0;
			fitness_t median = 0.0;
			fitness_t average = 0.0;
		};

		optimizer( const objective& o );
		virtual ~optimizer();

		virtual void run( const stop_condition& stop = stop_condition() ) { FLUT_NOT_IMPLEMENTED; }
		virtual void abort() { FLUT_NOT_IMPLEMENTED; }
		bool test_stop( const stop_condition& stop ) const;

		virtual fitness_vec_t evaluate( const vector< param_vec_t >& pop );
		
		int max_threads() const { return max_threads_; }
		void set_max_threads( int val ) { max_threads_ = val; }

		const vector< fitness_report >& history() const { return history_; }
		size_t current_generation() const { return history_.size(); }
		fitness_t current_fitness() const { return current_fitness_; }
		const param_vec_t& current_best() const { return current_best_; }

	protected:
		// evaluation settings
		int max_threads_ = 1;
		std::atomic_bool abort_flag_ = false;

		vector< fitness_report > history_;
		fitness_t current_fitness_;
		param_vec_t current_best_;

		const objective& objective_;
	};
}

#if defined(_MSC_VER)
#	pragma warning( pop )
#endif
