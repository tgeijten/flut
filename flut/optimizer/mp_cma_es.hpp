#pragma once

#include "cma_optimizer.hpp"

namespace flut
{
	class mp_cma_es : public optimizer
	{
	public:
		mp_cma_es( int dim, objective_func_t func ) : optimizer( dim, func ) {}
		virtual ~mp_cma_es() {}
		
	private:

	};
}
