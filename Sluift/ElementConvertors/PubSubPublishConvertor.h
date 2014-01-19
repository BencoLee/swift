/*
 * Copyright (c) 2013 Remko Tronçon
 * Licensed under the GNU General Public License.
 * See the COPYING file for more information.
 */

#pragma once

#include <Swiften/Base/Override.h>

#include <Sluift/GenericLuaElementConvertor.h>
#include <Swiften/Elements/PubSubPublish.h>

namespace Swift {
	class LuaElementConvertors;

	class PubSubPublishConvertor : public GenericLuaElementConvertor<PubSubPublish> {
		public:
			PubSubPublishConvertor(LuaElementConvertors* convertors);
			virtual ~PubSubPublishConvertor();

			virtual boost::shared_ptr<PubSubPublish> doConvertFromLua(lua_State*) SWIFTEN_OVERRIDE;
			virtual void doConvertToLua(lua_State*, boost::shared_ptr<PubSubPublish>) SWIFTEN_OVERRIDE;
			virtual boost::optional<Documentation> getDocumentation() const SWIFTEN_OVERRIDE;

		private:
			LuaElementConvertors* convertors;
	};
}