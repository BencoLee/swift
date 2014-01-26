/*
 * Copyright (c) 2013 Remko Tronçon
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#pragma clang diagnostic ignored "-Wunused-private-field"

#include <Swiften/Parser/PayloadParsers/PubSubEventSubscriptionParser.h>

#include <boost/optional.hpp>


#include <Swiften/Parser/PayloadParserFactoryCollection.h>
#include <Swiften/Parser/PayloadParserFactory.h>
#include <Swiften/Base/DateTime.h>
#include <Swiften/Parser/EnumParser.h>

using namespace Swift;

PubSubEventSubscriptionParser::PubSubEventSubscriptionParser(PayloadParserFactoryCollection* parsers) : parsers(parsers), level(0) {
}

PubSubEventSubscriptionParser::~PubSubEventSubscriptionParser() {
}

void PubSubEventSubscriptionParser::handleStartElement(const std::string& element, const std::string& ns, const AttributeMap& attributes) {
	if (level == 0) {
		if (boost::optional<std::string> attributeValue = attributes.getAttributeValue("node")) {
			getPayloadInternal()->setNode(*attributeValue);
		}
		if (boost::optional<std::string> attributeValue = attributes.getAttributeValue("jid")) {
			if (boost::optional<JID> jid = JID::parse(*attributeValue)) {
				getPayloadInternal()->setJID(*jid);
			}
		}
		if (boost::optional<std::string> attributeValue = attributes.getAttributeValue("subscription")) {
			if (boost::optional<PubSubEventSubscription::SubscriptionType> value = EnumParser<PubSubEventSubscription::SubscriptionType>()(PubSubEventSubscription::None, "none")(PubSubEventSubscription::Pending, "pending")(PubSubEventSubscription::Subscribed, "subscribed")(PubSubEventSubscription::Unconfigured, "unconfigured").parse(*attributeValue)) {
				getPayloadInternal()->setSubscription(*value);
			}
		}
		if (boost::optional<std::string> attributeValue = attributes.getAttributeValue("subid")) {
			getPayloadInternal()->setSubscriptionID(*attributeValue);
		}
		if (boost::optional<std::string> attributeValue = attributes.getAttributeValue("expiry")) {
				getPayloadInternal()->setExpiry(stringToDateTime(*attributeValue));
		}
	}

	

	if (level >= 1 && currentPayloadParser) {
		currentPayloadParser->handleStartElement(element, ns, attributes);
	}
	++level;
}

void PubSubEventSubscriptionParser::handleEndElement(const std::string& element, const std::string& ns) {
	--level;
	if (currentPayloadParser) {
		if (level >= 1) {
			currentPayloadParser->handleEndElement(element, ns);
		}

		if (level == 1) {
			
			currentPayloadParser.reset();
		}
	}
}

void PubSubEventSubscriptionParser::handleCharacterData(const std::string& data) {
	if (level > 1 && currentPayloadParser) {
		currentPayloadParser->handleCharacterData(data);
	}
}
