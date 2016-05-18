#pragma once

namespace flut
{
	namespace math
	{
		// generic class for values of a unit
		// work in progress
		template< typename UT, UT UV, typename T >
		struct unit_value
		{
			unit_value( const T& v ) : value( v ) {}
			T value;
		};

		//template< typename T > using rad_ = unit_value< angle_unit, angle_unit::radians, T >;
		//template< typename T > using deg_ = unit_value< angle_unit, angle_unit::degrees, T >;

		//template< typename UT, UT UV, typename T1, typename T2 >
		//unit_value< UT, UV, flut_result( T1, T2 ) > operator+( const unit_value< UT, UV, T1 >& a1, const unit_value< UT, UV, T2 >& a2 )
		//{ return unit_value< UT, UV, flut_result( T1, T2 ) >( a1.value + a2.value ); }

		//template< unit U, typename T1, typename T2 >
		//unit_value< U, flut_result( T1, T2 ) > operator-( const unit_value< U, T1 >& a1, const unit_value< U, T2 >& a2 )
		//{ return unit_value< U, flut_result( T1, T2 ) >( a1.value - a2.value ); }

		//template< typename T >
		//unit_value< angle_unit, angle_unit::radians, T > to_rad( const unit_value< angle_unit, angle_unit::degrees, T >& v )
		//{ return unit_value< angle_unit, angle_unit::radians, T >( deg_to_rad( v.value ) ); }
	}
}
