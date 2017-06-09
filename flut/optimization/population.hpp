#pragma once

#include "flut/system/types.hpp"
#include "search_point.hpp"
#include "objective.hpp"

#if defined(_MSC_VER)
#	pragma warning( push )
#	pragma warning( disable: 4251 )
#endif

namespace flut
{
	class FLUT_API population
	{
	public:
		population( const objective_info& inf ) : info_( inf ) {}

		size_t size() const { return individuals.size(); }

		index_t best_index() const;
		fitness_t best_fitness() const;
		fitness_t average_fitness() const;
		fitness_t median_fitness() const;

		pair< search_point, search_point > mean_std() const;

		vector< search_point > individuals;
		vector< fitness_t > fitnesses;

		const objective_info& info_;
	};
}

#if defined(_MSC_VER)
#	pragma warning( pop )
#endif
