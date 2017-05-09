#pragma once

#include "flut/circular_deque.hpp"

namespace flut
{
	class stop_condition
	{
	public:
		stop_condition() {}

		size_t max_generations;
		size_t min_progress;
		size_t progress_window_size;
	};
}
