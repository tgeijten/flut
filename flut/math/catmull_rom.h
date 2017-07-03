#pragma once

namespace flut
{
	template< typename P >
	struct catmull_rom_segment
	{
		catmull_rom_segment( const P& p0, const P& p1, const P& p2, const P& p3 ) :
		a_( 2 * p1 ),
		b_( -p0 + p2 ),
		c_( 2 * p0 - 5 * p1 + 4 * p2 - p3 ),
		d_( -p0 + 3 * p1 - 3 * p2 + p3 )
		{}

		template< typename T >
		P operator()( T t ) { return T( 0.5 ) * ( a_ + b_ * t + c_ * t * t + d_ * t * t * t ); }

	private:
		P a_, b_, c_, d_;
	};


	template< typename P, typename T >
	class catmull_rom
	{
	public:
		catmull_rom( const std::vector< P >& points, const std::vector< T >& times, T alpha = T( 0.5 ) ) :
		times_( times )
		{
			flut_assert( points.size() >= 4 && times.size() == ( points.size() - 2 ) );
			segments_.reserve( points.size() - 4 );
			for ( size_t i = 0; i <= points.size() - 4 )
				segments_.emplace_back( points[ i ], points[ i + 1 ], points[ i + 2 ], points[ i + 3 ] );
		}

		P operator()( T t ) {
			auto it = std::lower_bound( times_.begin(), times_.end(), t );
			if ( it == times_.end() ) it = times_.begin();
			if ( it == times_.end() - 1 ) it = times_.end() - 2;
			size_t index = it - times_.begin();
			return segments_[ index ]( ( t - *it ) / ( *( it + 1 ) - *it ) );
		}

	private:
		vector< catmull_rom_segment< P > > segments_;
		vector< T > times_;
	};
}
