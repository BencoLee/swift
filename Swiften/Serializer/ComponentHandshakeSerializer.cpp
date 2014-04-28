/*
 * Copyright (c) 2010-2014 Remko Tronçon
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#include <Swiften/Serializer/ComponentHandshakeSerializer.h>

#include <Swiften/Elements/ComponentHandshake.h>

namespace Swift {

ComponentHandshakeSerializer::ComponentHandshakeSerializer() {
}

SafeByteArray ComponentHandshakeSerializer::serialize(boost::shared_ptr<ToplevelElement> element)  const {
	boost::shared_ptr<ComponentHandshake> handshake(boost::dynamic_pointer_cast<ComponentHandshake>(element));
	return createSafeByteArray("<handshake>" + handshake->getData() + "</handshake>");
}

}
