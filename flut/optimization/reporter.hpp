#pragma once

#include "search_point.hpp"
#include "objective.hpp"

namespace flut
{
	class reporter
	{
	public:
		reporter() {}
		virtual ~reporter() {}

		struct generation_report
		{
			int instance;
			int generation;
			objective_info info;
			vector< search_point > par_sets;
			vector< fitness_t > fitnesses;
		};

		virtual void report_generation( const vector< search_point >& par_sets, const vector< fitness_t >& fitnesses ) {}
		virtual void report_new_best( const search_point& ps, fitness_t fitness ) {}

	protected:
	private:
	};
}
