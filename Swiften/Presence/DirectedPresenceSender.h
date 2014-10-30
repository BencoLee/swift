/*
 * Copyright (c) 2010-2014 Remko Tronçon
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#pragma once

#include <set>

#include <boost/optional.hpp>

#include <Swiften/Elements/Presence.h>
#include <Swiften/Presence/PresenceSender.h>
#include <Swiften/Base/API.h>

namespace Swift {
	class SWIFTEN_API DirectedPresenceSender : public PresenceSender {
		public:
			enum SendPresence {AndSendPresence, DontSendPresence};
			DirectedPresenceSender(PresenceSender*);

			void addDirectedPresenceReceiver(const JID&, SendPresence);
			void removeDirectedPresenceReceiver(const JID&, SendPresence);

			void sendPresence(Presence::ref);

			boost::optional<Presence::ref> getLastSentUndirectedPresence() const;

			bool isAvailable() const;

		private:
			boost::optional<Presence::ref> lastSentUndirectedPresence;
			PresenceSender* sender;
			std::set<JID> directedPresenceReceivers;
	};
}
