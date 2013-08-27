/*
 * Copyright (c) 2013 Remko Tronçon
 * Licensed under the GNU General Public License.
 * See the COPYING file for more information.
 */

#pragma once

#include <Swiften/Base/Override.h>
#include <Swiften/Base/API.h>
#include <Swiften/Serializer/GenericPayloadSerializer.h>
#include <Swiften/Elements/PubSubError.h>

namespace Swift {
	class PayloadSerializerCollection;

	class SWIFTEN_API PubSubErrorSerializer : public GenericPayloadSerializer<PubSubError> {
		public:
			PubSubErrorSerializer();
			virtual ~PubSubErrorSerializer();

			virtual std::string serializePayload(boost::shared_ptr<PubSubError>) const SWIFTEN_OVERRIDE;

		private:
			static std::string serializeType(PubSubError::Type);
			static std::string serializeUnsupportedFeatureType(PubSubError::UnsupportedFeatureType);
	};
}
