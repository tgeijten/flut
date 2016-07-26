#pragma once

#include "prop_node.hpp"

#define INIT_PROP( _pn_, _var_, _default_ ) _var_ = _pn_.get< decltype( _var_ ) >( #_var_, _default_ )
#define INIT_PROP_REQUIRED( _pn_, _var_ ) _var_ = _pn_.get< decltype( _var_ ) >( #_var_ )

namespace flut
{
	/// load the contents of an xml file into a prop_node
	prop_node FLUT_API read_xml( const string& filename );
}
