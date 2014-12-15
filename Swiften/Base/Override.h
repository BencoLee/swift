/*
 * Copyright (c) 2012 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#pragma once

#if defined(__clang__)
# if __has_feature(cxx_override_control) || __has_extension(cxx_override_control)
#  define SWIFTEN_OVERRIDE override
# else
#  define SWIFTEN_OVERRIDE
# endif

#elif defined(__GNUC__)
# if ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 7))) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#  define SWIFTEN_OVERRIDE override
# else
#  define SWIFTEN_OVERRIDE
# endif

#elif defined(_MSC_VER)
// Actually, 1700 is the first version that supports the C++11 override, but
// older versions apparently support a similar keyword.
# if _MSC_VER >= 1400
#  define SWIFTEN_OVERRIDE override
# else
#  define SWIFTEN_OVERRIDE
# endif

#else
# define SWIFTEN_OVERRIDE
#endif
