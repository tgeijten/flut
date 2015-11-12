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
