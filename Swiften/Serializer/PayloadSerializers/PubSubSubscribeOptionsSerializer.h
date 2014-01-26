/*
 * Copyright (c) 2013 Remko Tronçon
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#pragma once

#include <Swiften/Base/Override.h>
#include <Swiften/Base/API.h>
#include <Swiften/Serializer/GenericPayloadSerializer.h>
#include <Swiften/Elements/PubSubSubscribeOptions.h>
#include <boost/shared_ptr.hpp>

namespace Swift {
	class PayloadSerializerCollection;

	class SWIFTEN_API PubSubSubscribeOptionsSerializer : public GenericPayloadSerializer<PubSubSubscribeOptions> {
		public:
			PubSubSubscribeOptionsSerializer(PayloadSerializerCollection* serializers);
			virtual ~PubSubSubscribeOptionsSerializer();

			virtual std::string serializePayload(boost::shared_ptr<PubSubSubscribeOptions>) const SWIFTEN_OVERRIDE;

		private:
			

		private:
			PayloadSerializerCollection* serializers;
	};
}
