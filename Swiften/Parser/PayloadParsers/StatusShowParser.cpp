#include "Swiften/Parser/PayloadParsers/StatusShowParser.h"

namespace Swift {

StatusShowParser::StatusShowParser() : level_(0) {
}

void StatusShowParser::handleStartElement(const String&, const String&, const AttributeMap&) {
	++level_;
}

void StatusShowParser::handleEndElement(const String&, const String&) {
	--level_;
	if (level_ == 0) {
		if (text_ == "away") {
			getPayloadInternal()->setType(StatusShow::Away);
		}
		else if (text_ == "chat") {
			getPayloadInternal()->setType(StatusShow::FFC);
		}
		else if (text_ == "xa") {
			getPayloadInternal()->setType(StatusShow::XA);
		}
		else if (text_ == "dnd") {
			getPayloadInternal()->setType(StatusShow::DND);
		}
		else {
			getPayloadInternal()->setType(StatusShow::Online);
		}
	}
}

void StatusShowParser::handleCharacterData(const String& data) {
	text_ += data;
}

}
