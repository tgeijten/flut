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
		path( const string& p ) : data_( p ) {}
		path( string&& p ) : data_( std::move( p ) ) {}
		path( const path& p ) : data_( p.data_ ) {}
		path( path&& p ) : data_( std::move( p.data_ ) ) {}
		path( const char* p ) : data_( p ) {}

		path& operator=( const path& p ) { data_ = p.data_; return *this; }
		path& operator=( path&& p ) { data_ = std::move( p.data_ ); return *this; }
		path& operator=( const string& p ) { data_ = p; return *this; }
		path& operator=( string&& p ) { data_ = std::move( p ); return *this; }

		static char preferred_separator();

		const string& str() const { return data_; }
		const char* c_str() const { return data_.c_str(); }

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
		string data_;
	};

	FLUT_API path operator/( const path& p1, const path& p2 );
	FLUT_API path operator+( const path& p1, const string& p2 );
	FLUT_API path operator+( const string& p1, const path& p2 );
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
