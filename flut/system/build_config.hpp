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

#ifndef FLUT_USE_EXCEPTIONS
#define FLUT_USE_EXCEPTIONS 1
#endif

/// dynamic log levels are disabled in header only version
#ifdef FLUT_HEADER_ONLY
#define FLUT_ENABLE_DYNAMIC_LOG_LEVEL 0
#else
#define FLUT_ENABLE_DYNAMIC_LOG_LEVEL 1
#endif

#ifndef FLUT_LOG_LEVEL
#define FLUT_LOG_LEVEL FLUT_LOG_LEVEL_INFO
#endif

#ifndef FLUT_LOG_OUTPUT_STREAM
#define FLUT_LOG_OUTPUT_STREAM std::cout
#endif
