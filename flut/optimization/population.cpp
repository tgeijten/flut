#include "population.hpp"
#include <numeric>
#include "../container_tools.hpp"

namespace flut
{
	index_t population::best_index() const
	{
		if ( info_.minimize() )
			return std::min_element( fitnesses.begin(), fitnesses.end() ) - fitnesses.begin();
		else return std::max_element( fitnesses.begin(), fitnesses.end() ) - fitnesses.begin();
	}

	flut::fitness_t population::best_fitness() const
	{
		return fitnesses[ best_index() ];
	}

	flut::fitness_t population::average_fitness() const
	{
		return average( fitnesses );
	}

	flut::fitness_t population::median_fitness() const
	{
		return median( fitnesses );
	}

	pair< search_point, search_point > population::mean_std() const
	{
		vector< par_value > mean( info_.dim() );
		for ( auto& ind : individuals )
		{
			for ( index_t i = 0; i < info_.dim(); ++i )
				mean[ i ] += ind[ i ] / size();
		}

		vector< par_value > stds( info_.dim() );
		for ( index_t pop_idx = 0; pop_idx < size(); ++pop_idx )
		{
			for ( index_t i = 0; i < info_.dim(); ++i )
				stds[ i ] += math::squared( individuals[ pop_idx ][ i ] - mean[ i ] ) / size();
		}
		for ( index_t i = 0; i < info_.dim(); ++i )
			stds[ i ] = sqrt( stds[ i ] );

		return std::make_pair( search_point( info_, std::move( mean ) ), search_point( info_, std::move( stds ) ) );
	}

}
