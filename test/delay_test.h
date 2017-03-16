#pragma once

#include "flut/math/delayer.hpp"
#include "flut/buffer/storage.hpp"
#include "flut/math/math.hpp"
#include "flut/system/log.hpp"

namespace flut
{
	template< int N > void do_delay_test( float delay_inc, float dt, int times = 1 )
	{
		storage< float > sto;
		std::vector< delayer< float, N > > delvec;
		for ( int i = 1; i <= times; ++i )
			delvec.push_back( delayer< float, N >( i * delay_inc ) );

		for ( float t = 0; t < 1.0; t += dt )
		{
			auto f = sin( t * 8 * math::float_pi );
			sto.add_frame();
			sto[ "time" ] = t;
			sto[ "func" ] = f;

			for ( int i = 0; i < times; ++i )
			{
				auto delay_amount = ( i + 1 ) * delay_inc;
				delvec[ i ].add_sample( f, t == 0 ? 0.0f : dt );
				auto dd = delvec[ i ].delayed_value();
				auto df = t > delay_amount ? sin( ( t - delay_amount ) * 8 * math::float_pi ) : 0;
				sto[ stringf( "delay%.2f", delay_amount ) ] = dd;
				sto[ stringf( "fdelay%.2f", delay_amount ) ] = df;
				sto[ stringf( "error%.2f", delay_amount ) ] = dd - df;
			}
		}
		std::ofstream fs( stringf( "X:/test_%d_%.3f_%.3f.txt", N, delay_inc, dt ) );
		fs << sto;
	}

	void delay_test()
	{
		do_delay_test< 2 >( 0.01f, 0.002f, 5 );
		do_delay_test< 3 >( 0.01f, 0.002f, 5 );
		do_delay_test< 4 >( 0.01f, 0.002f, 5 );
	}
}
