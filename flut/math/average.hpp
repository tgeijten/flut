#pragma once

#include "flut/types.hpp"

namespace flut
{
	namespace math
	{
		template< typename T >
		struct average_
		{
			average_() : tot_v( T(0) ), tot_w( T(0) ) {}
			~average_() {}

			void add( T value, T w = T(1) ) { tot_v += w * value; tot_w += w; }
			T get() { return tot_w > T(0) ? tot_v / tot_w : T(0); }
			bool empty() { return tot_w == T(0); }
			void reset() { tot_v = tot_w = T(0); }

		private:
			T tot_v;
			T tot_w;
		};

		typedef average_< real_t > average;
	}
}
