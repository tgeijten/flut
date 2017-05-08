#pragma once

#include "optimizer.hpp"

namespace flut
{
	enum class cma_weights { equal = 0, linear = 1, log = 2 };

	class FLUT_API cma_optimizer : public optimizer
	{
	public:
		cma_optimizer( const objective& obj, int lambda = 0, int seed = 123, cma_weights weights = cma_weights::log );
		virtual ~cma_optimizer();

		// optimization
		const vector< param_vec_t >& sample_population();
		void update_distribution( const std::vector< fitness_t >& results );

		// analysis
		param_vec_t current_mean() const;
		param_vec_t current_std() const;
		const vector< param_vec_t >& current_pop() const;

		// actual parameters
		int dim() const;
		int lambda() const;
		int mu() const;
		int random_seed() const;
		double sigma() const;

	protected:
		struct pimpl_t* pimpl;
	};
}
