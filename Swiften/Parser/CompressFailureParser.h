/*
 * Copyright (c) 2010 Remko Tronçon
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#ifndef SWIFTEN_CompressFailureParser_H
#define SWIFTEN_CompressFailureParser_H

#include <Swiften/Parser/GenericElementParser.h>
#include <Swiften/Elements/CompressFailure.h>

namespace Swift {
	class CompressFailureParser : public GenericElementParser<CompressFailure> {
		public:
			CompressFailureParser() : GenericElementParser<CompressFailure>() {}
	};
}

#endif
