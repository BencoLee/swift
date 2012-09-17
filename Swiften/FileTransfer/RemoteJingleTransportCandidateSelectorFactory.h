/*
 * Copyright (c) 2011 Remko Tronçon
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#pragma once

#include <Swiften/Base/API.h>

namespace Swift {
	class RemoteJingleTransportCandidateSelector;

	class SWIFTEN_API RemoteJingleTransportCandidateSelectorFactory {
		public:
			virtual ~RemoteJingleTransportCandidateSelectorFactory();

			virtual RemoteJingleTransportCandidateSelector* createCandidateSelector() = 0;
	};
}
