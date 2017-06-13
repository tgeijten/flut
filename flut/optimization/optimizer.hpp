#pragma once

#include "flut/prop_node.hpp"
#include "flut/system/path.hpp"
#include "flut/system/types.hpp"
#include <functional>
#include "objective.hpp"
#include "flut/math/math.hpp"
#include <atomic>
#include "flut/math/optional_pod.hpp"
#include <thread>
#include "../system_tools.hpp"

#if defined(_MSC_VER)
#	pragma warning( push )
#	pragma warning( disable: 4251 )
#endif

namespace flut
{
	class FLUT_API optimizer
	{
	public:
		class FLUT_API callback
		{
		public:
			callback() {}
			virtual ~callback() {}
			virtual void start_cb( const optimizer& opt ) {}
			virtual void finish_cb( const optimizer& opt ) {}
			virtual void evaluate_cb( const search_point& point, fitness_t fitness_t ) {}
			virtual void evaluate_cb( const search_point_vec& pop, const fitness_vec_t& fitnesses ) {}
			virtual void next_generation_cb( size_t gen ) {}
			virtual void new_best_cb( const search_point& ps, fitness_t fitness ) {}
		};

		enum stop_condition { no_stop_condition, max_generations_reached, min_progress_reached, target_fitness_reached, user_abort };
		struct stop_condition_info
		{
			size_t max_generations = 10000;
			size_t progress_window_size = 100;
			fitness_t min_progress = 0;
			optional_pod< fitness_t > target_fitness;
		};

		optimizer( const objective& o );
		virtual ~optimizer();

		void optimize_background();

		virtual stop_condition run( const stop_condition_info& stop = stop_condition_info() );
		virtual stop_condition step( const stop_condition_info& ) { FLUT_NOT_IMPLEMENTED; }

		void add_callback( callback* cb ) { callbacks_.push_back( cb ); }

		void signal_abort() { abort_flag_ = true; }
		void abort_and_wait();
		bool test_abort() const { return abort_flag_; }

		stop_condition test_stop_condition( const stop_condition_info& stop ) const;
		fitness_vec_t evaluate( const search_point_vec& pop );
		
		int max_threads() const { return max_threads_; }
		void set_max_threads( int val ) { max_threads_ = val; }

		size_t generation_count() const { return step_count_; }
		fitness_t current_fitness() const { return current_fitness_; }

		const objective_info& info() const { return objective_.info(); }
		const objective& obj() const { return objective_; }

	protected:
		// evaluation settings
		int max_threads_ = 1;
		std::atomic_bool abort_flag_ = false;

		std::thread background_thread;
		flut::thread_priority thread_priority;

		size_t step_count_;
		fitness_t current_fitness_;

		const objective& objective_;

		vector< callback* > callbacks_;
	};
}

#if defined(_MSC_VER)
#	pragma warning( pop )
#endif
