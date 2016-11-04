#pragma once

#include <initializer_list>

namespace flut
{
	/// class for defining flags in a bitset
	template< typename EnumT, typename StorageT = unsigned int >
	struct flag_set
	{
		flag_set() : data( StorageT( 0 ) ) {}
		flag_set( const flag_set& o ) : data( o.data ) {}
		flag_set( std::initializer_list< EnumT >& flags ) : data( StorageT( 0 ) ) { for ( auto f : flags ) set( f ); }

		flag_set& operator=( const flag_set& o ) { data = o.data; return *this; }
		flag_set& operator|=( const flag_set& o ) { data |= o.data; return *this; }
		flag_set& operator&=( const flag_set& o ) { data &= o.data; return *this; }

		bool get( EnumT index ) { return ( data & ( 1 << index ) ) != 0; }
		flag_set& set( EnumT index, bool value = true ) { data = ( data & ~( StorageT(1) << index ) ) | ( StorageT(value) << index ); return *this; }

		template< EnumT index >	bool get() { return ( data & ( StorageT(1) << index ) ) != 0; }
		template< EnumT index > flag_set& set( bool value ) { data = ( data & ~( StorageT(1) << index ) ) | ( StorageT(value) << index ); return *this; }

		template< EnumT index > flag_set& set() { data |= StorageT(1) << index; return *this; }
		template< EnumT index > flag_set& reset() { data &= ~( StorageT(1) << index ); return *this; }

		void clear() { data = StorageT(0); }
		bool any() { return data != 0; }

	private:
		StorageT data;
	};
}
