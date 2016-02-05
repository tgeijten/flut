#pragma once

#include "build_config.hpp"

#include <stdexcept>
#include <cstdlib>

namespace flut
{
	struct exception : public std::runtime_error { exception( const std::string& msg ) : runtime_error( msg ) {} };
}

#if FLUT_USE_EXCEPTIONS
	#define FLUT_EXCEPTION( message_ ) throw flut::exception( message_ );
#else
	#define FLUT_EXCEPTION( message_ ) std::cout << message_ << std::endl; exit( -1 );
#endif


#if FLUT_USE_ASSERT
#define flut_assert( expression_ ) \
	if (!(expression_)) FLUT_EXCEPTION( "Assertion Failure in " + std::string( __FUNCTION__ ) + "(): "#expression_ );

	#define flut_assert_msg( expression_, message_ ) \
	if (!(expression_)) FLUT_EXCEPTION( "Assertion Failure in " + std::string( __FUNCTION__ ) + "(): "#expression_" (" + std::string( message_ ) + ")" );
#else
	#define flut_assert( expression_ )
	#define flut_assert_msg( expression_, message_ )
#endif

/// throw exception
#define flut_throw( message_ ) \
throw FLUT_EXCEPTION( std::string( __FUNCTION__ ) + "(): " + std::string( message_ ) )

/// conditional throw exception
#define flut_throw_if( condition_, message_ ) \
{ if ( condition_ ) FLUT_EXCEPTION( std::string( __func__ ) + "(): " + std::string( message_ ) ); }

/// not implemented exception
#define FLUT_NOT_IMPLEMENTED FLUT_EXCEPTION( std::string( __func__ ) + "(): Function not implemented" );
