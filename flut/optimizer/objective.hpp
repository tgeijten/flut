#pragma once

#include "flut/system/types.hpp"

namespace flut
{
	class objective
	{
	public:
		objective() {}
		virtual ~objective() {}

		virtual int dim() const = 0;
		virtual vector< double > initial_point() const { return vector< double >( dim(), 0.0 ); }
		virtual vector< double > initial_std() const { return vector< double >( dim(), 1.0 ); }
		virtual vector< double > upper_bounds() const { return vector< double >( dim(), 1e15 ); }
		virtual vector< double > lower_bounds() const { return vector< double >( dim(), -1e15 ); }
		virtual double evaluate( const vector< double >& point ) const = 0;
	};
}
