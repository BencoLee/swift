/*
 * Copyright (c) 2013 Remko Tronçon
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#pragma clang diagnostic ignored "-Wunused-private-field"

#include <Swiften/Parser/PayloadParsers/PubSubOwnerDeleteParser.h>

#include <boost/optional.hpp>


#include <Swiften/Parser/PayloadParserFactoryCollection.h>
#include <Swiften/Parser/PayloadParserFactory.h>
#include <Swiften/Parser/PayloadParsers/PubSubOwnerRedirectParser.h>

using namespace Swift;

PubSubOwnerDeleteParser::PubSubOwnerDeleteParser(PayloadParserFactoryCollection* parsers) : parsers(parsers), level(0) {
}

PubSubOwnerDeleteParser::~PubSubOwnerDeleteParser() {
}

void PubSubOwnerDeleteParser::handleStartElement(const std::string& element, const std::string& ns, const AttributeMap& attributes) {
	if (level == 0) {
		if (boost::optional<std::string> attributeValue = attributes.getAttributeValue("node")) {
			getPayloadInternal()->setNode(*attributeValue);
		}
	}

	if (level == 1) {
		if (element == "redirect" && ns == "http://jabber.org/protocol/pubsub#owner") {
			currentPayloadParser = boost::make_shared<PubSubOwnerRedirectParser>(parsers);
		}
	}

	if (level >= 1 && currentPayloadParser) {
		currentPayloadParser->handleStartElement(element, ns, attributes);
	}
	++level;
}

void PubSubOwnerDeleteParser::handleEndElement(const std::string& element, const std::string& ns) {
	--level;
	if (currentPayloadParser) {
		if (level >= 1) {
			currentPayloadParser->handleEndElement(element, ns);
		}

		if (level == 1) {
			if (element == "redirect" && ns == "http://jabber.org/protocol/pubsub#owner") {
				getPayloadInternal()->setRedirect(boost::dynamic_pointer_cast<PubSubOwnerRedirect>(currentPayloadParser->getPayload()));
			}
			currentPayloadParser.reset();
		}
	}
}

void PubSubOwnerDeleteParser::handleCharacterData(const std::string& data) {
	if (level > 1 && currentPayloadParser) {
		currentPayloadParser->handleCharacterData(data);
	}
}
