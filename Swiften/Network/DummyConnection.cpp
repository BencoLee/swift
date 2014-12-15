/*
 * Copyright (c) 2010 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#include <Swiften/Network/DummyConnection.h>

#include <boost/bind.hpp>
#include <boost/smart_ptr/make_shared.hpp>
#include <cassert>

namespace Swift {

DummyConnection::DummyConnection(EventLoop* eventLoop) : eventLoop(eventLoop) {
}

void DummyConnection::receive(const SafeByteArray& data) {
	eventLoop->postEvent(boost::bind(boost::ref(onDataRead), boost::make_shared<SafeByteArray>(data)), shared_from_this());
}

void DummyConnection::listen() {
	assert(false);
}

void DummyConnection::connect(const HostAddressPort&) {
	assert(false);
}


}
