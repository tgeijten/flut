#pragma once

#include "par_instance.hpp"
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
			par_info info;
			vector< par_instance > par_sets;
			vector< fitness_t > fitnesses;
		};

		virtual void report_generation( const vector< par_instance >& par_sets, const vector< fitness_t >& fitnesses ) {}
		virtual void report_new_best( const par_instance& ps, fitness_t fitness ) {}

	protected:
	private:
	};
}
