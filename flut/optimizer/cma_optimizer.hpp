#pragma once

#include "optimizer.hpp"

namespace flut
{
	enum class cma_weights { none = 0, equal = 1, linear = 2, log = 3 };

	class FLUT_API cma_optimizer : public optimizer
	{
	public:

		cma_optimizer( int dim,
			const real_vec& init_mean, const real_vec& init_std,
			int lambda = 0, int seed = 123,
			cma_weights w = cma_weights::log );

		cma_optimizer( int dim,
			const real_vec& init_mean, const real_vec& init_std,
			const real_vec& lower_bounds, const real_vec& upper_bounds,
			int lambda = 0, int seed = 123,
			cma_weights w = cma_weights::log );

		virtual ~cma_optimizer();

		void set_boundaries( const vector< double >& lower, const vector< double >& upper );

		const std::vector< std::vector< double > >& sample_population();
		void update_distribution( const std::vector< double >& results );

		int lambda() const;
		int mu() const;
		int dim() const;

	protected:
		struct pimpl_t* pimpl;
	};
}
