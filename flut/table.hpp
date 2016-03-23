#pragma once

#include "flut/types.hpp"
#include <iosfwd>
#include <vector>
#include "flut/container_tools.hpp"

namespace flut
{
	template< typename T >
	class table
	{
	public:
		table() {}
		virtual ~table() {}

		size_t add_row( const string& label, const T& default_value = T(0) ) {
			row_labels.push_back( label );
			data.push_back( std::vector< T >( columns(), default_value ) );
			return rows();
		}

		size_t add_column( const string& label, const T& default_value = T(0) ) {
			col_labels.push_back( label );
			for ( auto& row : data )
				row.resize( columns(), default_value );
			return columns();
		}

		size_t rows() const { return row_labels.size(); }
		size_t columns() const { return col_labels.size(); }

		index_t row_index( const string& label ) const { return find_index( row_labels, label ); }
		index_t column_index( const string& label ) const { return find_index( col_labels, label ); }

		const T& at( index_t row, index_t col ) const { flut_assert( row < rows() && col < columns() ); return data[ row ][ col ]; }
		T& at( index_t row, index_t col ) { flut_assert( row < rows() && col < columns() ); return data[ row ][ col ]; }

		/// set the value of a specific cell (must exist!)
		void set( index_t row, index_t col, const T& value ) { at( row, col ) = value; }
		const T& get( const string& row, const string& col ) const { return at( row_index( row ), column_index( col ) ); }

		void set( const string& row, const string& col, const T& value ) {
			auto ridx = row_index( row );
			if ( ridx == no_index ) ridx = add_row( row ) - 1;

			auto cidx = column_index( col );
			if ( cidx == no_index ) cidx = add_column( col ) - 1;

			set( row_index( row ), column_index( col ), value );
		}

		template< typename T1 >
		friend std::ostream& operator<<( std::ostream& str, const table< T1 >& t );

	private:

		vector< string > row_labels;
		vector< string > col_labels;
		vector< vector< T > > data;
	};

	template< typename T >
	std::ostream& operator<<( std::ostream& str, const table< T >& t ) {
		str << "Row";
		for ( auto& rl : t.col_labels )
			str << "\t" << rl;
		str << std::endl;

		for ( auto it = t.data.cbegin(); it != t.data.cend(); ++it ) {
			index_t rowidx = it - t.data.cbegin();
			str << t.row_labels[ rowidx ];
			for ( auto& v : *it )
				str << "\t" << v;
			str << std::endl;
		}

		return str;
	}
}
