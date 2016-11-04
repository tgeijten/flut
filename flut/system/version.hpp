#pragma once

#include "flut/system/types.hpp"
#include "flut/string_tools.hpp"

namespace flut
{
	struct version
	{
	public:
		version( int major, int minor, int maintenance, int build = 0, string postfix = "" ) :
			major_ver( major ), minor_ver( minor ), maintenance( maintenance ), build( build ), postfix( postfix ) {}

		version( const string& version ) {
			std::stringstream str( version );
			char dummy;
			str >> major_ver >> dummy >> minor_ver >> dummy >> maintenance >> dummy;
			if ( str.good() ) str >> build;
			if ( str.good() ) str >> postfix;
		}

		string to_str() const {
			string s = stringf( "%d.%d.%d", major_ver, minor_ver, maintenance );
			if ( build > 0 ) s += stringf( ".%d", build );
			if ( !postfix.empty() ) s += ' ' + postfix;
			return s;
		}

		int major_ver;
		int minor_ver;
		int maintenance;
		int build;

		string postfix;
	};

	inline std::ostream& operator<<( std::ostream& str, const version& ver ) { str << ver.to_str(); return str; }
}
