/*
 * Copyright (c) 2010 Remko Tronçon
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#pragma once

#include <string>

#include <Swiften/Base/API.h>

namespace Swift {
	class SWIFTEN_API IDNA {
		public:
			static std::string getEncoded(const std::string& s);
	};
}
