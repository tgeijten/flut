#pragma once

#include <numeric>

namespace flut
{
	template< typename IterX, typename IterY >
	class linear_regression
	{
	public:
		typedef typename IterX::value_type value_x_type;
		typedef typename IterY::value_type value_y_type;
		typedef decltype( value_x_type( 1 ) * value_y_type( 1 ) ) result_type;

		linear_regression( IterX x_begin, IterX x_end, IterY y_begin, IterY y_end )
		{
			auto n = x_end - x_begin;
			flut_assert_msg( n == y_end - y_begin, "Input ranges must be of equal size for x and y" );
			result_type avgx = std::accumulate( x_begin, x_end, result_type( 0 ) ) / n;
			result_type avgY = std::accumulate( y_begin, y_end, result_type( 0 ) ) / n;

			result_type num = 0.0;
			result_type den = 0.0;
			IterX itx = x_begin;
			IterY ity = y_begin;
			for (; itx != x_end; ++itx, ++ity )
			{
				num += ( *itx - avgx ) * ( *ity - avgY );
				den += ( *itx - avgx ) * ( *itx - avgx );
			}

			slope_ = num / den;
			offset_ = avgY - slope_ * avgx;
		}

		result_type slope() { return slope_; }
		result_type offset() { return offset_; }

	private:
		result_type slope_;
		result_type offset_;
	};

	template< typename I1, typename I2 >
	linear_regression< I1, I2 > do_linear_regression( I1 xb, I1 xe, I2 yb, I2 ye ) { return linear_regression< I1, I2 >( xb, xe, yb, ye ); }

	template< typename C1, typename C2 >
	linear_regression< typename C1::iterator, typename C2::iterator > do_linear_regression( C1& cx, C2& cy )
	{ return linear_regression< typename C1::iterator, typename C2::iterator >( cx.begin(), cx.end(), cy.begin(), cy.end() ); }
}
