/*
 * Copyright (c) 2010 Kevin Smith
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#ifndef SWIFTEN_EventController_H
#define SWIFTEN_EventController_H


#include "Swiften/Base/boost_bsignals.h"
#include <boost/shared_ptr.hpp>
#include <vector>

#include "Swift/Controllers/XMPPEvents/StanzaEvent.h"
#include "Swift/Controllers/XMPPEvents/MessageEvent.h"

namespace Swift {
	class EventController {
		public:
			EventController();
			void handleIncomingEvent(boost::shared_ptr<StanzaEvent> sourceEvent);
			boost::signal<void (int)> onEventQueueLengthChange;
			boost::signal<void (boost::shared_ptr<StanzaEvent>)> onEventQueueEventAdded;

		private:
			void handleEventConcluded(boost::shared_ptr<StanzaEvent> event);
			std::vector<boost::shared_ptr<StanzaEvent> > events_;
	};
}
#endif

