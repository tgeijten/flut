#pragma once

#include <array>

namespace flut
{
	template< typename T, int N = 2 >
	struct delayer
	{
		delayer( float delay = 1.0f, const T& init_value = T() ) : delay_( delay / ( N - 1 ) ), data_{ init_value }, idx_( 0 ), time_( 0 ) {
			static_assert( N >= 2, "flut::delayer resolution parameter must be >= 2" );
		}

		void add_sample( const T& value, float delta_time ) {
			time_ += delta_time;
			if ( time_ + 0.5f * delta_time > delay_ ) {
				time_ -= delay_;
				++idx_ %= N;
				data_[ idx_ ] = value;
			}
		}

		T delayed_value() const {
			auto w = time_ / delay_;
			return w * data_[ ( idx_ + N + 2 ) % N ] + ( 1.0f - w ) * data_[ ( idx_ + N + 1 ) % N ];
		}

		T operator()( const T& value, float delta_time ) { add_sample( value, delta_time ); return delayed_value(); }

		T operator()() { return delayed_value(); }

		float delay_;
		float time_;
		index_t idx_;
		std::array< T, N > data_;
	};
}
