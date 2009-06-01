#include "Swiften/Serializer/PayloadSerializers/DiscoInfoSerializer.h"

#include <boost/shared_ptr.hpp>

#include "Swiften/Base/foreach.h"
#include "Swiften/Serializer/XML/XMLElement.h"

namespace Swift {

DiscoInfoSerializer::DiscoInfoSerializer() : GenericPayloadSerializer<DiscoInfo>() {
}

String DiscoInfoSerializer::serializePayload(boost::shared_ptr<DiscoInfo> discoInfo)  const {
	XMLElement queryElement("query", "http://jabber.org/protocol/disco#info");
	if (!discoInfo->getNode().isEmpty()) {
		queryElement.setAttribute("node", discoInfo->getNode());
	}
	foreach(const DiscoInfo::Identity& identity, discoInfo->getIdentities()) {
		boost::shared_ptr<XMLElement> identityElement(new XMLElement("identity"));
		if (!identity.getLanguage().isEmpty()) {
			identityElement->setAttribute("xml:lang", identity.getLanguage());
		}
		identityElement->setAttribute("category", identity.getCategory());
		identityElement->setAttribute("name", identity.getName());
		identityElement->setAttribute("type", identity.getType());
		queryElement.addNode(identityElement);
	}
	foreach(const String& feature, discoInfo->getFeatures()) {
		boost::shared_ptr<XMLElement> featureElement(new XMLElement("feature"));
		featureElement->setAttribute("var", feature);
		queryElement.addNode(featureElement);
	}
	return queryElement.serialize();
}

}
