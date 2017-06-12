#pragma once

#include <initializer_list>

namespace flut
{
	/// class for defining flags in a bitset
	// TODO: use smart storage type
	template< typename EnumT, typename StorageT = unsigned int >
	struct flag_set
	{
		flag_set() : data( StorageT( 0 ) ) {}
		flag_set( const flag_set& o ) : data( o.data ) {}
		flag_set( std::initializer_list< EnumT > flags ) : data( StorageT( 0 ) ) { for ( auto f : flags ) set( f ); }

		flag_set& operator=( const flag_set& o ) { data = o.data; return *this; }

		inline const bool get( EnumT index ) const { return ( data & ( StorageT(1) << (int)index ) ) != 0; }
		inline const bool operator()( EnumT index ) const { return get( index ); }
		template< EnumT index >	bool get() const { return ( data & ( StorageT(1) << (int)index ) ) != 0; }

		flag_set& set( EnumT index, bool value = true ) { data = ( data & ~( StorageT(1) << (int)index ) ) | ( StorageT(value) << (int)index ); return *this; }
		template< EnumT index > flag_set& set( bool value ) { data = ( data & ~( StorageT(1) << (int)index ) ) | ( StorageT(value) << (int)index ); return *this; }
		template< EnumT index > flag_set& set() { data |= StorageT(1) << (int)index; return *this; }
		template< EnumT index > flag_set& reset() { data &= ~( StorageT(1) << (int)index ); return *this; }

		void clear() { data = StorageT(0); }
		bool any() const { return data != 0; }

	private:
		StorageT data;
	};
}
