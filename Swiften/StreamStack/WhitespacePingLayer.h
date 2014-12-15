/*
 * Copyright (c) 2010 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#pragma once

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include <Swiften/StreamStack/StreamLayer.h>

namespace Swift {
	class Timer;
	class TimerFactory;

	class WhitespacePingLayer : public StreamLayer, boost::noncopyable {
		public:
			WhitespacePingLayer(TimerFactory* timerFactory);

			void setActive();
			void setInactive();
			void writeData(const SafeByteArray& data);
			void handleDataRead(const SafeByteArray& data);

			bool getIsActive() const {
				return isActive;
			}

		private:
			void handleTimerTick();

		private:
			bool isActive;
			boost::shared_ptr<Timer> timer;
	};
}
