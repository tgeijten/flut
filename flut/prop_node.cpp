#include "prop_node.hpp"

#include <stdio.h>
#include <memory>
#include <iomanip>

namespace flut
{
	std::ostream& prop_node::to_stream( std::ostream& str, int depth, int align ) const
	{
		if ( align == 0 )
			align = get_align_width( depth );

		for ( auto& child : children )
		{
			string key_str( depth * 2, ' ' );
			key_str += child.first;

			str << std::left << std::setw( align ) << key_str;
			if ( child.second.has_value() || child.second.children.size() == 0 )
				str << std::setw( 0 ) << " = " << child.second.get_value();
			str << std::endl;

			child.second.to_stream( str, depth + 1, align );
		}

		return str;
	}

	int prop_node::get_align_width( int depth ) const
	{
		int width = 0;
		for ( auto& child : children )
		{
			width = std::max( width, depth * 2 + int( child.first.size() ) );
			width = std::max( width, child.second.get_align_width( depth + 1 ) );
		}
		return width;
	}
}
