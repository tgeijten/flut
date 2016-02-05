#pragma once

namespace flut
{
	template< typename EnumT, typename StorageT = unsigned int >
	struct flags
	{
		template< EnumT index >
		bool get() { return ( data & ( 1 << index ) ) != 0; }

		bool get( EnumT index ) { return ( data & ( 1 << index ) ) != 0; }
		void set( EnumT index, bool value ) { data = ( data & ~( 1 << index ) ) | ( StorageT(value) << index ); }
		void clear() { data = StorageT( 0 ); }

	private:
		StorageT data;
	};
}
