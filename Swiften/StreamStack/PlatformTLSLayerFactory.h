/*
 * Copyright (c) 2010 Remko Tronçon
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#pragma once

#include "Swiften/StreamStack/TLSLayerFactory.h"

namespace Swift {
	class PlatformTLSLayerFactory : public TLSLayerFactory {
		public:
			PlatformTLSLayerFactory();

			bool canCreate() const;
			virtual boost::shared_ptr<TLSLayer> createTLSLayer();
	};
}
