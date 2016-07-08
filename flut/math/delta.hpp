#pragma once

namespace flut
{
	template< typename T >
	struct delta 
	{
		delta( const T& initial_value = T(0) ) : previous( initial_value ) {}
		void reset( const T& initial_value = T(0) ) { previous = initial_value; }
		T operator()( const T& new_value ) { T result = new_value - previous; previous = new_value; return result; }

		const T& value() { return previous; }
		T delta_value( const T& new_value ) { return new_value - previous; }

	private:
		T previous;
	};
}
