/*
 * Copyright (c) 2010-2013 Remko Tronçon
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#pragma once

#include <sstream>

#include <Swiften/Base/API.h>

namespace Swift {
	class SWIFTEN_API Log {
		public:
			enum Severity {
				error, warning, info, debug
			};

			Log();
			~Log();

			std::ostringstream& getStream(
					Severity severity, 
					const std::string& severityString, 
					const std::string& file, 
					int line,
					const std::string& function);

			static Severity getLogLevel();
			static void setLogLevel(Severity level);

		private:
			std::ostringstream stream;
	};
}

#define SWIFT_LOG(severity) \
	if (Log::severity > Log::getLogLevel()) ; \
	else Log().getStream(Log::severity, #severity, __FILE__, __LINE__, __FUNCTION__)
