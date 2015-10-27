#pragma once

#include <stdexcept>
#include <cstdlib>

namespace fluc
{
	struct Exception : public std::runtime_error { Exception( const std::string& msg ) : runtime_error( msg ) {} };
}

#define USE_FLUC_ASSERT 1

#if USE_FLUC_ASSERT

#define FLUC_CRITICAL_ERROR( message_ ) throw fluc::Exception( message_ );

#define fluc_assert( expression_ ) \
if (!(expression_)) throw fluc::Exception( "Assertion Failure in " + std::string( __func__ ) + "(): "#expression_ );

#define fluc_assert_msg( expression_, message_ ) \
if (!(expression_)) throw fluc::Exception( "Assertion Failure in " + std::string( __func__ ) + "(): "#expression_" (" + std::string( message_ ) + ")" );

#define fluc_throw( message_ ) \
throw fluc::Exception( std::string( __func__ ) + "(): " + std::string( message_ ) )

#define fluc_throw_if( condition_, message_ ) \
{ if ( condition_ ) throw fluc::Exception( std::string( __func__ ) + "(): " + std::string( message_ ) ); }

#else

#define FLUC_CRITICAL_ERROR( message_ ) std::cout << message_ << std::endl; exit( -1 );

#endif

#define fluc_not_implemented FLUC_CRITICAL_ERROR( std::string( __func__ ) + "(): Function not implemented" );
