/*
 * Copyright (c) 2010 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#include <Swiften/Network/BoostIOServiceThread.h>

#include <boost/smart_ptr/make_shared.hpp>

namespace Swift {

BoostIOServiceThread::BoostIOServiceThread() {
	ioService_ = boost::make_shared<boost::asio::io_service>();
	thread_ = new boost::thread(boost::bind(&BoostIOServiceThread::doRun, this));
}

BoostIOServiceThread::~BoostIOServiceThread() {
	ioService_->stop();
	thread_->join();
	delete thread_;
}

void BoostIOServiceThread::doRun() {
	boost::asio::io_service::work work(*ioService_);
	ioService_->run();
}

}
