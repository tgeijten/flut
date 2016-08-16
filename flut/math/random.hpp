#pragma once

#include "flut/system/prerequisites.hpp"
#include <random>

#ifdef FLUT_COMP_MSVC
#	pragma warning( push )
#	pragma warning( disable: 4251 )
#endif

namespace flut
{
	namespace math
	{
		struct FLUT_API random_number_generator
		{
			random_number_generator( size_t seed = 123 ) : engine( seed ) {}
			void seed( size_t s ) { engine.seed( s ); }
			template< typename T > T uni( T min = T( 0 ), T max = T( 1 ) ) { return std::uniform_real_distribution<T>( min, max )( engine ); }
			template< typename T > T norm( T mean, T stdev ) { return std::normal_distribution<T>( mean, stdev )( engine ); }

			static random_number_generator& global_instance() { return global_generator; }

		private:
			// #TODO: use faster & less accurate engine
			std::default_random_engine engine;
			static random_number_generator global_generator;
		};
	}

	template< typename T > T rand_uni( T min, T max ) { return math::random_number_generator::global_instance().uni( min, max ); }
	template< typename T > T rand_norm( T mean, T stdev ) { return math::random_number_generator::global_instance().norm( mean, stdev ); }
}

#ifdef FLUT_COMP_MSVC
#	pragma warning( pop )
#endif
