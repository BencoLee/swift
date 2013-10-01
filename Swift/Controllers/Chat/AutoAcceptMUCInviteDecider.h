/*
 * Copyright (c) 2013 Tobias Markmann
 * Licensed under the simplified BSD license.
 * See Documentation/Licenses/BSD-simplified.txt for more information.
 */

#pragma once

#include <Swiften/Roster/XMPPRoster.h>
#include <Swiften/Elements/MUCInvitationPayload.h>
#include <Swift/Controllers/Settings/SettingsProvider.h>
#include <Swift/Controllers/SettingConstants.h>

namespace Swift {
	class AutoAcceptMUCInviteDecider {
		public:
			AutoAcceptMUCInviteDecider(const JID& domain, XMPPRoster* roster, SettingsProvider* settings) : domain_(domain), roster_(roster), settings_(settings) {
			}

			bool isAutoAcceptedInvite(const JID& from, MUCInvitationPayload::ref invite) {
				if (!invite->getIsImpromptu() && !invite->getIsContinuation()) {
					return false;
				}

				std::string auto_accept_mode = settings_->getSetting(SettingConstants::INVITE_AUTO_ACCEPT_MODE);
				if (auto_accept_mode == "no") {
					return false;
				} else if (auto_accept_mode == "presence") {
					return roster_->getSubscriptionStateForJID(from) == RosterItemPayload::From || roster_->getSubscriptionStateForJID(from) == RosterItemPayload::Both;
				} else if (auto_accept_mode == "domain") {
					return roster_->getSubscriptionStateForJID(from) == RosterItemPayload::From || roster_->getSubscriptionStateForJID(from) == RosterItemPayload::Both || from.getDomain() == domain_;
				} else {
					assert(false);
				}
			}

		private:
			JID domain_;
			XMPPRoster* roster_;
			SettingsProvider* settings_;
	};
}
