#pragma once

#include <numeric>
#include "math.hpp"

namespace flut
{
	template< typename T >
	class linear_regression
	{
	public:
		template< typename IterX, typename IterY >
		linear_regression( IterX x_begin, IterX x_end, IterY y_begin, IterY y_end )
		{
			auto n = x_end - x_begin;
			flut_assert_msg( n == y_end - y_begin, "Input ranges must be of equal size for x and y" );
			T avgx = average( x_begin, x_end );
			T avgY = average( y_begin, y_end );
			T num = 0.0;
			T den = 0.0;
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

		template< typename IterY >
		linear_regression( T x_begin, T x_step, IterY y_begin, IterY y_end )
		{
			auto n = y_end - y_begin;
			T avgx = x_begin + ( ( n - 1 ) * x_step ) / 2;
			T avgY = average( y_begin, y_end );
			T num = 0.0;
			T xval = x_begin;
			for ( IterY ity = y_begin; ity != y_end; ++ity, xval += x_step )
				num += ( xval - avgx ) * ( *ity - avgY );

			// analytical solution for den with fixed steps
			T x_hsiz = ( n - 1 ) * x_step / 2;
			T den = x_hsiz * ( x_hsiz + x_step ) * ( 2 * x_hsiz + x_step ) / ( 3 * x_step );

			slope_ = num / den;
			offset_ = avgY - slope_ * avgx;
		}

		T slope() { return slope_; }
		T offset() { return offset_; }

	private:
		T slope_;
		T offset_;
	};

	template< typename I1, typename I2 >
	auto make_linear_regression( I1 xb, I1 xe, I2 yb, I2 ye ) { return linear_regression< typename I1::value_type >( xb, xe, yb, ye ); }

	template< typename C1, typename C2 >
	auto make_linear_regression( const C1& cx, const C2& cy )
	{ return linear_regression< result_type< typename C1::value_type, typename C2::value_type >::type >( cx.begin(), cx.end(), cy.begin(), cy.end() ); }

	template< typename C >
	auto make_linear_regression( typename C::value_type x_begin, typename C::value_type x_step, const C& cy )
	{ return linear_regression< typename C::value_type >( x_begin, x_step, cy.begin(), cy.end() ); }
}
