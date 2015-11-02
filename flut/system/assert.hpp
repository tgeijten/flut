#pragma once

#include <stdexcept>
#include <cstdlib>

namespace flut
{
	struct Exception : public std::runtime_error { Exception( const std::string& msg ) : runtime_error( msg ) {} };
}

#define FLUT_USE_EXCEPTIONS 1

#if FLUT_USE_EXCEPTIONS

#define FLUT_CRITICAL_ERROR( message_ ) throw flut::Exception( message_ );

#define flut_assert( expression_ ) \
if (!(expression_)) throw flut::Exception( "Assertion Failure in " + std::string( __func__ ) + "(): "#expression_ );

#define flut_assert_msg( expression_, message_ ) \
if (!(expression_)) throw flut::Exception( "Assertion Failure in " + std::string( __func__ ) + "(): "#expression_" (" + std::string( message_ ) + ")" );

#define flut_throw( message_ ) \
throw flut::Exception( std::string( __func__ ) + "(): " + std::string( message_ ) )

#define flut_throw_if( condition_, message_ ) \
{ if ( condition_ ) throw flut::Exception( std::string( __func__ ) + "(): " + std::string( message_ ) ); }

#else

#define FLUT_CRITICAL_ERROR( message_ ) std::cout << message_ << std::endl; exit( -1 );

#endif

#define FLUT_NOT_IMPLEMENTED FLUT_CRITICAL_ERROR( std::string( __func__ ) + "(): Function not implemented" );
