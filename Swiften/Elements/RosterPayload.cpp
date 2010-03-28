#include "Swiften/Elements/RosterPayload.h"
#include "Swiften/Base/foreach.h"

namespace Swift {

boost::optional<RosterItemPayload> RosterPayload::getItem(const JID& jid) const {
	foreach(const RosterItemPayload& item, items_) {
		// FIXME: MSVC rejects this. Find out why.
		//if (item.getJID() == jid) {
		if (item.getJID().equals(jid, JID::WithResource)) {
			return boost::optional<RosterItemPayload>(item);
		}
	}
	return boost::optional<RosterItemPayload>();
}

}
