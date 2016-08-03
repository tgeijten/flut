#pragma once

namespace flut
{
	/// class for defining flags in a bitset
	template< typename EnumT, typename StorageT = unsigned int >
	struct flag_set
	{
		flag_set() : data( StorageT( 0 ) ) { }

		template< EnumT index >
		bool get() { return ( data & ( StorageT(1) << index ) ) != 0; }
		bool get( EnumT index ) { return ( data & ( 1 << index ) ) != 0; }

		void set( EnumT index, bool value ) { data = ( data & ~( StorageT(1) << index ) ) | ( StorageT(value) << index ); }

		template< EnumT index >
		void set( bool value ) { data = ( data & ~( StorageT(1) << index ) ) | ( StorageT(value) << index ); }

		template< EnumT index >
		void set() { data |= StorageT(1) << index; }

		template< EnumT index >
		void reset() { data &= ~( StorageT(1) << index ); }

		void clear() { data = StorageT(0); }
		bool any() { return data != 0; }

	private:
		StorageT data;
	};
}
