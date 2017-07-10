#pragma once

#include "flut/system/types.hpp"
#include <iosfwd>
#include <vector>
#include "flut/container_tools.hpp"

namespace flut
{
	template< typename T, typename L = string >
	class table
	{
	public:
		table( size_t rows = 0, size_t cols = 0 ) : row_labels( rows ), col_labels( cols ), data( rows * cols ) {}
		~table() {}

		index_t add_row( const L& label, const T& default_value = T(0) ) {
			row_labels.add( label );
			data.resize( row_size() * column_size(), default_value );
			return row_size() - 1;
		}

		index_t add_column( const L& label, const T& default_value = T(0) ) {
			resize( row_size(), column_size() + 1 );
			return col_labels.set_back( label );
		}

		void resize( size_t rows, size_t cols ) {
			flut_error_if( rows < row_size() || cols < column_size(), "Cannot shrink table" );

			// reorganize existing data
			data.resize( row_size * cols );
			for ( index_t ri = rows; ri-- > 0; )
				for ( index_t ci = cols; ci-- > 0 )
					data_[ cols * ri + ci ] = ( ri < row_size() && ci < column_size() ) ? data[ column_size() * ri + ci ] : T(0);
			col_labels.resize( cols );
			row_labels.resize( rows );
		}

		size_t row_size() const { return row_labels.size(); }
		size_t column_size() const { return col_labels.size(); }

		const T& operator()( index_t row, index_t col ) const { flut_assert( row < row_size() && col < column_size() ); return data[ row * column_size() + col ]; }
		T& operator()( index_t row, index_t col ) { flut_assert( row < row_size() && col < column_size() ); return data[ row * column_size() + col ]; }

		/// set the value of a specific cell (must exist!)
		void set( index_t row, index_t col, const T& value ) { at( row, col ) = value; }
		const T& get( const L& row, const L& col ) const { return at( row_index( row ), column_index( col ) ); }

		void set( const L& row, const L& col, const T& value ) {
			auto ridx = row_index( row );
			if ( ridx == no_index ) ridx = add_row( row ) - 1;

			auto cidx = column_index( col );
			if ( cidx == no_index ) cidx = add_column( col ) - 1;

			set( row_index( row ), column_index( col ), value );
		}

		template< typename T1 >
		friend std::ostream& operator<<( std::ostream& str, const table< T1 >& t );

	private:

		data_header< L > row_labels;
		data_header< L > col_labels;
		vector< T > data;
	};

	template< typename T >
	std::ostream& operator<<( std::ostream& str, const table< T >& t ) {
		str << "Row";
		for ( auto& rl : t.col_labels )
			str << "\t" << rl;
		str << std::endl;

		for ( index_t row = 0; row < t.row_size(); ++row )
		{
			str << t.row_labels[ row ];
			for ( index_t col = 0; col < t.column_size(); ++col )
				str << "\t" << t( row, col );
			str << std::endl;
		}

		return str;
	}
}
