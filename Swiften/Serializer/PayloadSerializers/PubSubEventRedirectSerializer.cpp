/*
 * Copyright (c) 2013 Remko Tronçon
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#pragma clang diagnostic ignored "-Wunused-private-field"

#include <Swiften/Serializer/PayloadSerializers/PubSubEventRedirectSerializer.h>
#include <Swiften/Serializer/XML/XMLElement.h>


#include <Swiften/Serializer/PayloadSerializerCollection.h>


using namespace Swift;

PubSubEventRedirectSerializer::PubSubEventRedirectSerializer(PayloadSerializerCollection* serializers) : serializers(serializers) {
}

PubSubEventRedirectSerializer::~PubSubEventRedirectSerializer() {
}

std::string PubSubEventRedirectSerializer::serializePayload(boost::shared_ptr<PubSubEventRedirect> payload) const {
	if (!payload) {
		return "";
	}
	XMLElement element("redirect", "http://jabber.org/protocol/pubsub#event");
	element.setAttribute("uri", payload->getURI());
	return element.serialize();
}


