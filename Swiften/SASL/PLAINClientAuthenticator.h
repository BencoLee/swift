/*
 * Copyright (c) 2010 Remko Tronçon
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#pragma once

#include <Swiften/SASL/ClientAuthenticator.h>

namespace Swift {
	class PLAINClientAuthenticator : public ClientAuthenticator {
		public:
			PLAINClientAuthenticator();

			virtual boost::optional<ByteArray> getResponse() const;
			virtual bool setChallenge(const boost::optional<ByteArray>&);
	};
}
