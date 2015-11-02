#pragma once

#include <random>

namespace flut
{
	namespace math
	{
		template< typename T >
		struct random
		{
			random( size_t seed ) : engine( seed ) {}
			T uni( T min = T( 0 ), T max = T( 1 ) ) { return std::uniform_real_distribution<T>( min, max )( engine ); }
			T norm( T mean, T stdev ) { return std::normal_distribution<T>( mean, stdev )( engine ); }

		private:
			std::default_random_engine engine;
		};
	}
}
