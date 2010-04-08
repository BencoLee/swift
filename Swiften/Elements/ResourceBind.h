/*
 * Copyright (c) 2010 Remko Tronçon
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#ifndef SWIFTEN_ResourceBind_H
#define SWIFTEN_ResourceBind_H

#include "Swiften/Base/String.h"
#include "Swiften/Elements/Payload.h"
#include "Swiften/JID/JID.h"

namespace Swift {
	class ResourceBind : public Payload
	{
		public:
			ResourceBind() {}

			void setJID(const JID& jid) {
				jid_ = jid;
			}

			const JID& getJID() const { 
				return jid_; 
			}

			void setResource(const String& resource) {
				resource_ = resource;
			}

			const String& getResource() const {
				return resource_; 
			}

		private:
			JID jid_;
			String resource_;
	};
}

#endif
