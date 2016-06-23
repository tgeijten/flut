#pragma once

#if defined(_MSC_VER)
#	ifdef FLUT_EXPORTS
#		define FLUT_API __declspec(dllexport)
#	else
#		define FLUT_API __declspec(dllimport)
#	endif
#	define FLUT_COMP_MSVC
#else
#	define FLUT_API
#endif
