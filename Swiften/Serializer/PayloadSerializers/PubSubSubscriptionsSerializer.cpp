/*
 * Copyright (c) 2013 Remko Tronçon
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#pragma clang diagnostic ignored "-Wunused-private-field"

#include <Swiften/Serializer/PayloadSerializers/PubSubSubscriptionsSerializer.h>
#include <Swiften/Serializer/XML/XMLElement.h>
#include <boost/smart_ptr/make_shared.hpp>

#include <Swiften/Serializer/PayloadSerializerCollection.h>
#include <Swiften/Base/foreach.h>
#include <Swiften/Serializer/PayloadSerializers/PubSubSubscriptionSerializer.h>
#include <Swiften/Serializer/XML/XMLRawTextNode.h>

using namespace Swift;

PubSubSubscriptionsSerializer::PubSubSubscriptionsSerializer(PayloadSerializerCollection* serializers) : serializers(serializers) {
}

PubSubSubscriptionsSerializer::~PubSubSubscriptionsSerializer() {
}

std::string PubSubSubscriptionsSerializer::serializePayload(boost::shared_ptr<PubSubSubscriptions> payload) const {
	if (!payload) {
		return "";
	}
	XMLElement element("subscriptions", "http://jabber.org/protocol/pubsub");
	if (payload->getNode()) {
		element.setAttribute("node", *payload->getNode());
	}
	foreach(boost::shared_ptr<PubSubSubscription> item, payload->getSubscriptions()) {
		element.addNode(boost::make_shared<XMLRawTextNode>(PubSubSubscriptionSerializer(serializers).serialize(item)));
	}
	return element.serialize();
}


