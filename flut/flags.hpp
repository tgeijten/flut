#pragma once

namespace flut
{
	template< typename EnumT, typename StorageT = unsigned int >
	struct flags
	{
		bool get( EnumT index ) { return ( data & ( 1 << index ) ) != 0; }
		void set( EnumT index, bool value ) { data = ( data & ~( 1 << index ) ) | ( 1 << index ); }
		void clear() { data = StorageT( 0 ); }

	private:
		StorageT data;
	};
}
