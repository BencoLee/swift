#ifndef SWIFTEN_StatusShowParser_H
#define SWIFTEN_StatusShowParser_H

#include "Swiften/Elements/StatusShow.h"
#include "Swiften/Parser/GenericPayloadParser.h"

namespace Swift {
	class StatusShowParser : public GenericPayloadParser<StatusShow> {
		public:
			StatusShowParser();

			virtual void handleStartElement(const String& element, const String&, const AttributeMap& attributes);
			virtual void handleEndElement(const String& element, const String&);
			virtual void handleCharacterData(const String& data);

		private:
			int level_;
			String text_;
	};
}

#endif
