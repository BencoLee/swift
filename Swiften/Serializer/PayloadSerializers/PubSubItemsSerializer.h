/*
 * Copyright (c) 2013 Remko Tronçon
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#pragma once

#include <Swiften/Base/Override.h>
#include <Swiften/Base/API.h>
#include <Swiften/Serializer/GenericPayloadSerializer.h>
#include <Swiften/Elements/PubSubItems.h>
#include <boost/shared_ptr.hpp>

namespace Swift {
	class PayloadSerializerCollection;

	class SWIFTEN_API PubSubItemsSerializer : public GenericPayloadSerializer<PubSubItems> {
		public:
			PubSubItemsSerializer(PayloadSerializerCollection* serializers);
			virtual ~PubSubItemsSerializer();

			virtual std::string serializePayload(boost::shared_ptr<PubSubItems>) const SWIFTEN_OVERRIDE;

		private:
			

		private:
			PayloadSerializerCollection* serializers;
	};
}
