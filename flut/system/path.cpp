#include "path.hpp"

namespace flut
{

	char path::preferred_separator()
	{
		return '/';
	}

	path& path::replace_extension( const path& ext )
	{
		size_t n = data.find_last_of( '.' );
		if ( n == string::npos ) data += '.' + ext.data;
		else data = data.substr( 0, n + 1 ) + ext.data;
		return *this;
	}

	path& path::remove_filename()
	{
		size_t n = last_separator_pos();
		if ( n != string::npos ) data = data.substr( 0, n );
		else data.clear();
		return *this;
	}


	path& path::replace_filename( const path& f )
	{
		remove_filename();
		return *this /= f;
	}

	flut::path& path::make_preferred()
	{
		for ( char& c : data )
			if ( c == '/' || c == '\\' ) c = preferred_separator();
		return *this;
	}

	flut::path path::parent_path() const
	{
		size_t n = last_separator_pos();
		return n != string::npos ? data.substr( 0, n ) : path();
	}

	flut::path path::extension() const
	{
		size_t n = data.find_last_of( '.' );
		return n != string::npos ? path( data.substr( n + 1 ) ) : path();
	}

	flut::path path::filename() const
	{
		size_t n = last_separator_pos();
		return n != string::npos ? path( data.substr( n + 1 ) ) : path();
	}

	flut::path path::stem()
	{
		size_t n1 = last_separator_pos();
		size_t n2 = data.find_last_of( '.' );
		if ( n1 == string::npos ) n1 = 0; else ++n1;
		return path( data.substr( n1, ( n2 >= n1 ) ? n2 - n1 : string::npos ) );
	}

	bool path::empty() const
	{
		return data.empty();
	}

	bool path::has_filename() const
	{
		return last_separator_pos() != data.size() - 1;
	}

	size_t path::last_separator_pos() const
	{
		return data.find_last_of( "/\\" );
	}

	flut::path& path::operator/=( const path& p )
	{
		if ( has_filename() ) data += preferred_separator() + p.data;
		else data += p.data;
		return *this;
	}

	flut::path operator/( const path& p1, const path& p2 )
	{
		return p1.has_filename() ? path( p1.str() + path::preferred_separator() + p2.str() ) : path( p1.str() + p2.str() );
	}

	flut::path operator+( const path& p1, const string& p2 )
	{
		return path( p1.str() + p2 );
	}

	std::ostream& operator<<( std::ostream& str, const path& p )
	{
		str << p.str(); return str;
	}

	bool operator!=( const path& p1, const path& p2 )
	{
		return p1.str() != p2.str();
	}

	bool operator==( const path& p1, const path& p2 )
	{
		return p1.str() == p2.str();
	}

}
