#pragma once

#include "prop_node.hpp"
#include "system/path.hpp"
#include "error_code.h"

#define INIT_PROP( _pn_, _var_, _default_ ) _var_ = _pn_.get< decltype( _var_ ) >( #_var_, decltype( _var_ )( _default_ ) )
#define INIT_PROP_NAMED( _pn_, _var_, _name_, _default_ ) _var_ = _pn_.get< decltype( _var_ ) >( _name_, _default_ )
#define INIT_PROP_REQUIRED( _pn_, _var_ ) _var_ = _pn_.get< decltype( _var_ ) >( #_var_ )
#define INIT_PROP_NAMED_REQUIRED( _pn_, _var_, _name_ ) _var_ = _pn_.get< decltype( _var_ ) >( _name_ )

#define SET_PROP( _pn_, _var_ ) _pn_.set< decltype( _var_ ) >( #_var_, _var_ )
#define SET_PROP_NAMED( _pn_, _var_, _name_ ) _pn_.set< decltype( _var_ ) >( _name_, _var_ )

namespace flut
{
	/// load contents from file (auto detect)
	FLUT_API prop_node load_file( const path& filename );

	/// load/save contents from xml
	FLUT_API prop_node load_xml( const path& filename, error_code* ec = nullptr  );
	FLUT_API void save_xml( const prop_node& pn, const path& filename );

	/// load/save contents from prop
	FLUT_API prop_node load_prop( const path& filename, error_code* ec = nullptr );
	FLUT_API bool save_prop( const prop_node& pn, const path& filename, bool readable = true );

	/// load contents from prop
	FLUT_API prop_node load_ini( const path& filename );
	FLUT_API void save_ini( const prop_node& pn, const path& filename );

	/// merge prop_nodes
	FLUT_API void merge_prop_nodes( prop_node& pn, const prop_node& other, bool overwrite );

	/// insert prop_nodes
	FLUT_API prop_node load_file_with_include( const path& filename, const string& include_directive = "INCLUDE", int level = 0 );
}
