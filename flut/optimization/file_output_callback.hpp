#pragma once

#include "search_point.hpp"
#include "objective.hpp"
#include "optimizer.hpp"

namespace flut
{
	class file_output_callback : public optimizer::callback
	{
	public:
		file_output_callback() {}
		virtual ~file_output_callback() {}

	};
}
