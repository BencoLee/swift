#include "Swiften/Roster/XMPPRoster.h"

namespace Swift {

void XMPPRoster::addContact(const JID& jid, const String& name, const std::vector<String>& groups, RosterItemPayload::Subscription subscription) {
	JID bareJID(jid.toBare());
	bool exists = containsJID(bareJID);
	String oldName = getNameForJID(bareJID);
	std::vector<String> oldGroups = entries_[bareJID].groups;
	if (exists) {
		entries_.erase(bareJID);
	}
	XMPPRosterItem item;
	item.groups = groups;
	item.name = name;
	item.jid = jid;
	item.subscription = subscription;
	entries_[bareJID] = item;
	if (exists) {
		onJIDUpdated(bareJID, oldName, oldGroups);
	} else {
		onJIDAdded(bareJID);
	}
}

void XMPPRoster::removeContact(const JID& jid) {
	entries_.erase(JID(jid.toBare()));
	onJIDRemoved(jid);
}

bool XMPPRoster::containsJID(const JID& jid) {
	return entries_.find(JID(jid.toBare())) != entries_.end();
}

const String& XMPPRoster::getNameForJID(const JID& jid) {
	return entries_[JID(jid.toBare())].name;
}

const std::vector<String>& XMPPRoster::getGroupsForJID(const JID& jid) {
	return entries_[JID(jid.toBare())].groups;
}

RosterItemPayload::Subscription XMPPRoster::getSubscriptionStateForJID(const JID& jid) {
	return entries_[JID(jid.toBare())].subscription;
}

}

