/*
 * Copyright (c) 2010-2013 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#include <Swiften/Jingle/JingleSession.h>

#include <boost/smart_ptr/make_shared.hpp>
#include <algorithm>
#include <boost/function.hpp>

#include <Swiften/Base/foreach.h>

using namespace Swift;

JingleSession::JingleSession(const JID& initiator, const std::string& id) : initiator(initiator), id(id) {
	// initiator must always be a full JID; session lookup based on it wouldn't work otherwise
	// this is checked on an upper level so that the assert never fails
	assert(!initiator.isBare());
}

JingleSession::~JingleSession() {
}
