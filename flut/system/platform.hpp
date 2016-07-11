#pragma once

#if defined(_MSC_VER)
#	ifdef FLUT_EXPORTS
#		define FLUT_API __declspec(dllexport)
#	else
#		define FLUT_API __declspec(dllimport)
#	endif
#	define _CRT_SECURE_NO_WARNINGS
#	define FLUT_COMP_MSVC
#else
#	define FLUT_API
#endif
