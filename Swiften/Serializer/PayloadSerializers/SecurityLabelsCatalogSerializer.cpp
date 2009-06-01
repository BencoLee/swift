#include "Swiften/Serializer/PayloadSerializers/SecurityLabelsCatalogSerializer.h"
#include "Swiften/Base/foreach.h"
#include "Swiften/Serializer/XML/XMLElement.h"
#include "Swiften/Serializer/XML/XMLRawTextNode.h"
#include "Swiften/Serializer/PayloadSerializers/SecurityLabelSerializer.h"

namespace Swift {

SecurityLabelsCatalogSerializer::SecurityLabelsCatalogSerializer() : GenericPayloadSerializer<SecurityLabelsCatalog>() {
}

String SecurityLabelsCatalogSerializer::serializePayload(boost::shared_ptr<SecurityLabelsCatalog> catalog)  const {
	XMLElement element("catalog", "urn:xmpp:sec-label:catalog:0");
	if (!catalog->getName().isEmpty()) {
		element.setAttribute("name", catalog->getName());
	}
	if (catalog->getTo().isValid()) {
		element.setAttribute("to", catalog->getTo());
	}
	if (!catalog->getDescription().isEmpty()) {
		element.setAttribute("desc", catalog->getDescription());
	}
	foreach (const SecurityLabel& label, catalog->getLabels()) {
		String serializedLabel = SecurityLabelSerializer().serialize(boost::shared_ptr<SecurityLabel>(new SecurityLabel(label)));
		element.addNode(boost::shared_ptr<XMLRawTextNode>(new XMLRawTextNode(serializedLabel)));
	}
	return element.serialize();
}

}
