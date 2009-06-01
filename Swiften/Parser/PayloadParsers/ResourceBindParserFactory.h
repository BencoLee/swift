#ifndef SWIFTEN_ResourceBindParserFactory_H
#define SWIFTEN_ResourceBindParserFactory_H

#include "Swiften/Parser/GenericPayloadParserFactory.h"
#include "Swiften/Parser/PayloadParsers/ResourceBindParser.h"

namespace Swift {
	class ResourceBindParserFactory : public GenericPayloadParserFactory<ResourceBindParser> {
		public:
			ResourceBindParserFactory() : GenericPayloadParserFactory<ResourceBindParser>("bind", "urn:ietf:params:xml:ns:xmpp-bind") {}
	};
}

#endif
