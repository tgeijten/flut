#include "prop_node.hpp"

#include <stdio.h>
#include <memory>
#include <iomanip>

namespace flut
{
	int get_align_width( const prop_node& pn, int depth )
	{
		int width = 0;
		for ( auto& child : pn )
		{
			width = std::max( width, depth * 2 + int( child.first.size() ) );
			width = std::max( width, get_align_width( child.second, depth + 1 ) );
		}
		return width;
	}

	std::ostream& to_stream( std::ostream& str, const prop_node& pn, int depth, int align )
	{
		if ( align == 0 )
			align = get_align_width( pn, depth );

		for ( auto& child : pn )
		{
			string key_str( depth * 2, ' ' );
			key_str += child.first;

			str << std::left << std::setw( align ) << key_str;
			if ( child.second.has_value() || child.second.size() == 0 )
				str << std::setw( 0 ) << " = " << child.second.get_value();
			str << std::endl;

			to_stream( str, child.second, depth + 1, align );
		}

		return str;
	}
}
