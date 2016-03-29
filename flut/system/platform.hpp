#pragma once

#if defined(_MSC_VER)
	#ifdef FLUT_EXPORTS
		#define FLUT_API __declspec(dllexport)
	#else
		#define FLUT_API __declspec(dllimport)
	#endif
#else
	#define FLUT_API
#endif

#ifdef WIN32
	#define NOMINMAX
	#define WIN32_LEAN_AND_MEAN
	#include <shlwapi.h> // used by glob_match
	#undef small
	#pragma comment( lib, "shlwapi.lib" )
#endif
