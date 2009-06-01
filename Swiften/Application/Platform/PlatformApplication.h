#ifndef SWIFTEN_PlatformApplication_H
#define SWIFTEN_PlatformApplication_H

#include "Swiften/Base/Platform.h"


#if defined(SWIFTEN_PLATFORM_MACOSX)
#include "Swiften/Application/MacOSX/MacOSXApplication.h"
namespace Swift {
	typedef MacOSXApplication PlatformApplication;
}
#elif defined(SWIFTEN_PLATFORM_WIN32)
#include "Swiften/Application/Windows/WindowsApplication.h"
namespace Swift {
	typedef WindowsApplication PlatformApplication;
}
#else
#include "Swiften/Application/Unix/UnixApplication.h"
namespace Swift {
	typedef UnixApplication PlatformApplication;
}
#endif

#endif
