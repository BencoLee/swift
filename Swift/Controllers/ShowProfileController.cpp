/*
 * Copyright (c) 2012 Tobias Markmann
 * Licensed under the simplified BSD license.
 * See Documentation/Licenses/BSD-simplified.txt for more information.
 */

/*
 * Copyright (c) 2014 Kevin Smith and Remko Tronçon
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#include "ShowProfileController.h"

#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <Swiften/Base/foreach.h>
#include <Swiften/VCards/VCardManager.h>

#include <Swift/Controllers/UIEvents/ShowProfileForRosterItemUIEvent.h>
#include <Swift/Controllers/UIEvents/UIEventStream.h>
#include <Swift/Controllers/UIInterfaces/ProfileWindowFactory.h>

namespace Swift {

ShowProfileController::ShowProfileController(VCardManager* vcardManager, ProfileWindowFactory* profileWindowFactory, UIEventStream* uiEventStream) : vcardManager(vcardManager), profileWindowFactory(profileWindowFactory), uiEventStream(uiEventStream) {
	uiEventStream->onUIEvent.connect(boost::bind(&ShowProfileController::handleUIEvent, this, _1));
	vcardManager->onVCardChanged.connect(boost::bind(&ShowProfileController::handleVCardChanged, this, _1, _2));
}

ShowProfileController::~ShowProfileController() {
	typedef std::pair<JID, ProfileWindow*> JIDProfileWindowPair;
	foreach(const JIDProfileWindowPair& jidWndPair, openedProfileWindows) {
		jidWndPair.second->onWindowAboutToBeClosed.disconnect(boost::bind(&ShowProfileController::handleProfileWindowAboutToBeClosed, this, _1));
		delete jidWndPair.second;
	}

	vcardManager->onVCardChanged.disconnect(boost::bind(&ShowProfileController::handleVCardChanged, this, _1, _2));
	uiEventStream->onUIEvent.disconnect(boost::bind(&ShowProfileController::handleUIEvent, this, _1));
}

void ShowProfileController::handleUIEvent(UIEvent::ref event) {
	ShowProfileForRosterItemUIEvent::ref showProfileEvent = boost::dynamic_pointer_cast<ShowProfileForRosterItemUIEvent>(event);
	if (!showProfileEvent) {
		return;
	}

	if (openedProfileWindows.find(showProfileEvent->getJID()) == openedProfileWindows.end()) {
		ProfileWindow* newProfileWindow = profileWindowFactory->createProfileWindow();
		newProfileWindow->setJID(showProfileEvent->getJID());
		newProfileWindow->onWindowAboutToBeClosed.connect(boost::bind(&ShowProfileController::handleProfileWindowAboutToBeClosed, this, _1));
		openedProfileWindows[showProfileEvent->getJID()] = newProfileWindow;
		VCard::ref vcard = vcardManager->getVCardAndRequestWhenNeeded(showProfileEvent->getJID(), boost::posix_time::minutes(5));
		if (vcard) {
			newProfileWindow->setVCard(vcard);
		} else {
			newProfileWindow->setProcessing(true);
		}
		newProfileWindow->show();
	} else {
		openedProfileWindows[showProfileEvent->getJID()]->show();
	}
}

void ShowProfileController::handleVCardChanged(const JID& jid, VCard::ref vcard) {
	if (openedProfileWindows.find(jid) == openedProfileWindows.end()) {
		return;
	}

	ProfileWindow* profileWindow = openedProfileWindows[jid];
	profileWindow->setVCard(vcard);
	profileWindow->setProcessing(false);
	profileWindow->show();
}

void ShowProfileController::handleProfileWindowAboutToBeClosed(const JID& profileJid) {
	openedProfileWindows.erase(profileJid);
}

}
