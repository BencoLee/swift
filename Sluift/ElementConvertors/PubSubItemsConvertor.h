/*
 * Copyright (c) 2013 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#pragma once

#include <Swiften/Base/Override.h>

#include <Sluift/GenericLuaElementConvertor.h>
#include <Swiften/Elements/PubSubItems.h>

namespace Swift {
	class LuaElementConvertors;

	class PubSubItemsConvertor : public GenericLuaElementConvertor<PubSubItems> {
		public:
			PubSubItemsConvertor(LuaElementConvertors* convertors);
			virtual ~PubSubItemsConvertor();

			virtual boost::shared_ptr<PubSubItems> doConvertFromLua(lua_State*) SWIFTEN_OVERRIDE;
			virtual void doConvertToLua(lua_State*, boost::shared_ptr<PubSubItems>) SWIFTEN_OVERRIDE;
			virtual boost::optional<Documentation> getDocumentation() const SWIFTEN_OVERRIDE;

		private:
			LuaElementConvertors* convertors;
	};
}
