#pragma once

#ifndef FLUT_USE_EXCEPTIONS
#	define FLUT_USE_EXCEPTIONS 1
#endif

#if FLUT_USE_EXCEPTIONS
#	ifndef FLUT_USE_ASSERT
#		define FLUT_USE_ASSERT 1
#	endif
#endif
