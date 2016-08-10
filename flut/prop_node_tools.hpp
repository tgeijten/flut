#pragma once

#include "prop_node.hpp"

#define INIT_PROP( _pn_, _var_, _default_ ) _var_ = _pn_.get< decltype( _var_ ) >( #_var_, _default_ )
#define INIT_PROP_NAMED( _pn_, _var_, _name_, _default_ ) _var_ = _pn_.get< decltype( _var_ ) >( _name_, _default_ )
#define INIT_PROP_REQUIRED( _pn_, _var_ ) _var_ = _pn_.get< decltype( _var_ ) >( #_var_ )
#define INIT_PROP_NAMED_REQUIRED( _pn_, _var_, _name_ ) _var_ = _pn_.get< decltype( _var_ ) >( _name_ )

namespace flut
{
	/// load the contents of an xml file into a prop_node
	prop_node FLUT_API load_xml( const string& filename );
	prop_node FLUT_API load_prop( const string& filename );
	void FLUT_API save_prop( const prop_node& pn, const string& filename, bool readable );
}
