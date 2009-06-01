#ifndef SWIFTEN_TLSProceedSerializer_H
#define SWIFTEN_TLSProceedSerializer_H

#include <boost/shared_ptr.hpp>

#include "Swiften/Elements/TLSProceed.h"
#include "Swiften/Serializer/GenericElementSerializer.h"
#include "Swiften/Serializer/XML/XMLElement.h"

namespace Swift {
	class TLSProceedSerializer : public GenericElementSerializer<TLSProceed> {
		public:
			TLSProceedSerializer() : GenericElementSerializer<TLSProceed>() {
			}

			virtual String serialize(boost::shared_ptr<Element>) const {
				return XMLElement("proceed", "urn:ietf:params:xml:ns:xmpp-tls").serialize();
			}
	};
}

#endif
