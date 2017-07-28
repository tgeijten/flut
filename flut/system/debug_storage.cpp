#include "debug_storage.hpp"
#include "flut/storage.hpp"
#include "flut/math/math.hpp"
#include <fstream>

namespace flut
{
	template< typename T, typename L >
	struct auto_storage_writer
	{
		auto_storage_writer( const path filename ) : filename_( filename ) {}
		~auto_storage_writer() {
			if ( !storage_.empty() )
				std::ofstream( filename_.str() ) << storage_;
		}

		void write( const L& label, T value ) {
			auto idx = storage_.find_or_add_channel( label, constantsf::sentinel() );
			if ( storage_.empty() || storage_[ idx ] != constantsf::sentinel() )
				storage_.add_frame( constantsf::sentinel() );
			storage_[ idx ] = value;
		}
		path filename_;
		storage< T, L > storage_;
	};

	auto_storage_writer< float, string > g_debug_storage_writer( "debug.txt" );

	void set_debug_output( const path& filename )
	{
		g_debug_storage_writer.filename_ = filename;
	}

	void write_debug( const string& label, float data )
	{
		g_debug_storage_writer.write( label, data );
	}
}
