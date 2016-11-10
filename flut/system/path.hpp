#pragma once

#include "types.hpp"
#include "string_cast.hpp"

namespace flut
{
	class path
	{
	public:
		path() {}
		path( string&& p ) : data( std::move( p ) ) {}
		path( const path&& p ) : data( std::move( p.data ) ) {}
		path( const string& p ) : data( p ) {}
		path( const path& p ) : data( p.data ) {}
		path( const char* p ) : data( p ) {}

		path& operator=( const path& p ) { data = p.data; return *this; }
		path& operator=( const path&& p ) { data = std::move( p.data ); return *this; }

		static char preferred_separator() { return '/'; }

		const string& str() const { return data; }

		path& replace_extension( const path& ext ) {
			size_t n = data.find_last_of( '.' );
			if ( n == string::npos ) data += '.' + ext.data;
			else data = data.substr( 0, n + 1 ) + ext.data;
			return *this;
		}

		path& remove_filename() {
			size_t n = last_separator_pos();
			if ( n != string::npos ) data = data.substr( 0, n );
			else data.clear();
			return *this;
		}

		path& replace_filename( const path& f ) {
			remove_filename();
			return *this /= f;
		}

		path& make_preferred() {
			for ( char& c : data )
				if ( c == '/' || c == '\\' ) c = preferred_separator();
			return *this;
		}

		path parent_path() const {
			size_t n = last_separator_pos();
			return n != string::npos ? data.substr( 0, n ) : data;
		}

		path extension() const {
			size_t n = data.find_last_of( '.' );
			return n != string::npos ? path( data.substr( n + 1 ) ) : path();
		}

		path filename() const {
			size_t n = last_separator_pos();
			return n != string::npos ? path( data.substr( n + 1 ) ) : path();
		}

		path stem() {
			size_t n1 = last_separator_pos();
			size_t n2 = data.find_last_of( '.' );
			if ( n1 == string::npos ) n1 = 0; else ++n1;
			return path( data.substr( n1, ( n2 >= n1 ) ? n2 - n1 : string::npos ) );
		}

		bool empty() const { return data.empty(); }

		path& operator/=( const path& p )
		{
			if ( has_filename() ) data += preferred_separator() + p.data;
			else data += p.data;
			return *this;
		}

		bool has_filename() const {
			return last_separator_pos() != data.size() - 1;
		}

	private:
		size_t last_separator_pos() const { return data.find_last_of( "/\\" ); }
		string data;
	};

	inline path operator/( const path& p1, const path& p2 ) {
		return p1.has_filename() ? path( p1.str() + path::preferred_separator() + p2.str() ) : path( p1.str() + p2.str() );
	}

	inline bool operator==( const path& p1, const path& p2 ) { return p1.str() == p2.str(); }
	inline bool operator!=( const path& p1, const path& p2 ) { return p1.str() != p2.str(); }

	inline std::ostream& operator<<( std::ostream& str, const path& p ) { str << p.str(); return str; }

	template<> struct string_cast< path, void > {
		static path from( const string& s ) { return path( s ); }
		static string to( const path& value ) { return value.str(); }
	};
}
