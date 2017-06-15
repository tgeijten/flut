#pragma once

#include "flut/system/platform.hpp"
#include "search_point.hpp"

namespace flut
{
	class optimizer;

	class FLUT_API reporter
	{
	public:
		reporter() {}
		virtual ~reporter() {}

		virtual void start_cb( const optimizer& opt ) {}
		virtual void finish_cb( const optimizer& opt ) {}
		virtual void evaluate_cb( const search_point& point, fitness_t fitness_t ) {}
		virtual void evaluate_cb( const search_point_vec& pop, const fitness_vec_t& fitnesses ) {}
		virtual void next_generation_cb( size_t gen ) {}
		virtual void new_best_cb( const search_point& ps, fitness_t fitness ) {}
	};

	class FLUT_API file_reporter : public reporter
	{
	public:
		file_reporter() {}
		virtual ~file_reporter() {}

		virtual void start_cb( const optimizer& opt ) {}
		virtual void finish_cb( const optimizer& opt ) {}
		virtual void evaluate_cb( const search_point& point, fitness_t fitness_t ) {}
		virtual void evaluate_cb( const search_point_vec& pop, const fitness_vec_t& fitnesses ) {}
		virtual void next_generation_cb( size_t gen ) {}
		virtual void new_best_cb( const search_point& ps, fitness_t fitness ) {}

	};
}
