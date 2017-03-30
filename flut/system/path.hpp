#pragma once

#include "platform.hpp"
#include "types.hpp"
#include "string_cast.hpp"

#ifdef FLUT_COMP_MSVC
#	pragma warning( push )
#	pragma warning( disable: 4251 )
#endif

namespace flut
{
	class FLUT_API path
	{
	public:
		path() {}
		path( const string& p ) : data( p ) {}
		path( string&& p ) : data( std::move( p ) ) {}
		path( const path& p ) : data( p.data ) {}
		path( path&& p ) : data( std::move( p.data ) ) {}
		path( const char* p ) : data( p ) {}

		path& operator=( const path& p ) { data = p.data; return *this; }
		path& operator=( path&& p ) { data = std::move( p.data ); return *this; }

		static char preferred_separator();

		const string& str() const { return data; }
		const char* c_str() const { return data.c_str(); }

		path& replace_extension( const path& ext = "" );
		path& remove_filename();
		path& replace_filename( const path& f = "" );
		path& make_preferred();
		path parent_path() const;
		path extension() const;
		path filename() const;
		path stem();
		bool empty() const;
		path& operator/=( const path& p );
		bool has_filename() const;

	private:
		size_t last_separator_pos() const;
		string data;
	};

	FLUT_API path operator/( const path& p1, const path& p2 );
	FLUT_API path operator+( const path& p1, const string& p2 );
	FLUT_API bool operator==( const path& p1, const path& p2 );
	FLUT_API bool operator!=( const path& p1, const path& p2 );
	FLUT_API std::ostream& operator<<( std::ostream& str, const path& p );

	template<> struct string_cast< path, void > {
		static path from( const string& s ) { return path( s ); }
		static string to( const path& value ) { return value.str(); }
	};
}

#ifdef FLUT_COMP_MSVC
#	pragma warning( pop )
#endif
