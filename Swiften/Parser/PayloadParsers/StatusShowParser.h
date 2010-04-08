/*
 * Copyright (c) 2010 Remko Tronçon
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

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
