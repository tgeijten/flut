#pragma once

#include "prop_node.hpp"

#define INIT_PROP( _pn_, _var_, _default_ ) _var_ = _pn_.get< decltype( _var_ ) >( #_var_, _default_ )
#define INIT_PROP_NAMED( _pn_, _var_, _name_, _default_ ) _var_ = _pn_.get< decltype( _var_ ) >( _name_, _default_ )
#define INIT_PROP_REQUIRED( _pn_, _var_ ) _var_ = _pn_.get< decltype( _var_ ) >( #_var_ )
#define INIT_PROP_NAMED_REQUIRED( _pn_, _var_, _name_ ) _var_ = _pn_.get< decltype( _var_ ) >( _name_ )

namespace flut
{
	/// load contents from xml
	FLUT_API prop_node load_xml( const string& filename );

	/// load contents from prop
	FLUT_API prop_node load_prop( const string& filename );

	/// save contents to prop
	FLUT_API void save_prop( const prop_node& pn, const string& filename, bool readable );

	/// merge prop_nodes
	FLUT_API void merge_prop_nodes( prop_node& pn, const prop_node& other, bool overwrite );
}
