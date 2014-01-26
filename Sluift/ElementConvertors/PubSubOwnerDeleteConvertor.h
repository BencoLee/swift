/*
 * Copyright (c) 2013 Remko Tronçon
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#pragma once

#include <Swiften/Base/Override.h>

#include <Sluift/GenericLuaElementConvertor.h>
#include <Swiften/Elements/PubSubOwnerDelete.h>

namespace Swift {
	class LuaElementConvertors;

	class PubSubOwnerDeleteConvertor : public GenericLuaElementConvertor<PubSubOwnerDelete> {
		public:
			PubSubOwnerDeleteConvertor(LuaElementConvertors* convertors);
			virtual ~PubSubOwnerDeleteConvertor();

			virtual boost::shared_ptr<PubSubOwnerDelete> doConvertFromLua(lua_State*) SWIFTEN_OVERRIDE;
			virtual void doConvertToLua(lua_State*, boost::shared_ptr<PubSubOwnerDelete>) SWIFTEN_OVERRIDE;
			virtual boost::optional<Documentation> getDocumentation() const SWIFTEN_OVERRIDE;

		private:
			LuaElementConvertors* convertors;
	};
}
