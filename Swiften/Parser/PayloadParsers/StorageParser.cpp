#include "Swiften/Parser/PayloadParsers/StorageParser.h"

#include <cassert>

namespace Swift {

StorageParser::StorageParser() : level(TopLevel) {
}

void StorageParser::handleStartElement(const String& element, const String&, const AttributeMap& attributes) {
	if (level == BookmarkLevel) {
		if (element == "conference") {
			assert(!conference);
			conference = Storage::Conference();
			conference->autoJoin = attributes.getBoolAttribute("autojoin", false);
			conference->jid = JID(attributes.getAttribute("jid"));
			conference->name = attributes.getAttribute("name");
		}
	}
	else if (level == DetailLevel) {
		currentText = "";
	}
	++level;
}

void StorageParser::handleEndElement(const String& element, const String&) {
	--level;
	if (level == BookmarkLevel) {
		if (element == "conference") {
			assert(conference);
			getPayloadInternal()->addConference(*conference);
			conference.reset();
		}
	}
	else if (level == DetailLevel && conference) {
		if (element == "nick") {
			conference->nick = currentText;
		}
		else if (element == "password") {
			conference->password = currentText;
		}
	}
}

void StorageParser::handleCharacterData(const String& data) {
	currentText += data;
}

}
