#include "Swiften/Queries/Request.h"
#include "Swiften/Queries/IQRouter.h"
#include "Swiften/EventLoop/MainEventLoop.h"

namespace Swift {

Request::Request(IQ::Type type, const JID& receiver, boost::shared_ptr<Payload> payload, IQRouter* router, AutoDeleteBehavior autoDeleteBehavior) : router_(router), type_(type), receiver_(receiver), payload_(payload), autoDeleteBehavior_(autoDeleteBehavior), sent_(false) {
}

void Request::send() {
	assert(!sent_);
	sent_ = true;

	boost::shared_ptr<IQ> iq(new IQ(type_));
	iq->setTo(receiver_);
	iq->addPayload(payload_);
	id_ = router_->getNewIQID();
	iq->setID(id_);
	router_->addHandler(this);
	router_->sendIQ(iq);
}

bool Request::handleIQ(boost::shared_ptr<IQ> iq) {
	bool handled = false;
	if (sent_ && iq->getID() == id_) {
		if (iq->getType() == IQ::Result) {
			handleResponse(iq->getPayloadOfSameType(payload_), boost::optional<Error>());
		}
		else {
			// FIXME: Get proper error
			handleResponse(boost::shared_ptr<Payload>(), boost::optional<Error>(Error::UndefinedCondition));
		}
		router_->removeHandler(this);
		if (autoDeleteBehavior_ == AutoDeleteAfterResponse) {
			MainEventLoop::deleteLater(this);
		}
		handled = true;
	}
	return handled;
}

}
