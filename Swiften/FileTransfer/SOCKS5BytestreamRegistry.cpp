/*
 * Copyright (c) 2010-2013 Remko Tronçon
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#include <Swiften/FileTransfer/SOCKS5BytestreamRegistry.h>

#include <boost/smart_ptr/make_shared.hpp>

#include <Swiften/Base/Algorithm.h>
#include <Swiften/Base/Log.h>
#include <Swiften/Base/foreach.h>

namespace Swift {

SOCKS5BytestreamRegistry::SOCKS5BytestreamRegistry() {
}

void SOCKS5BytestreamRegistry::setHasBytestream(const std::string& destination, bool b) {
	if (b) {
		availableBytestreams.insert(destination);
	}
	else {
		availableBytestreams.erase(destination);
	}
}

bool SOCKS5BytestreamRegistry::hasBytestream(const std::string& destination) const {
	return availableBytestreams.find(destination) != availableBytestreams.end();
}

std::string SOCKS5BytestreamRegistry::generateSessionID() {
	return idGenerator.generateID();
}

}

