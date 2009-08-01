#pragma once

#include <boost/optional.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <vector>

#include "Swiften/Network/Connection.h"
#include "Swiften/Network/HostAddressPort.h"
#include "Swiften/EventLoop/EventOwner.h"
#include "Swiften/EventLoop/MainEventLoop.h"

namespace Swift {
	class FakeConnection : 
			public Connection, 
			public EventOwner,
			public boost::enable_shared_from_this<FakeConnection> {
		public:
			enum State {
				Initial,
				Connecting,
				Connected,
				Disconnected,
				DisconnectedWithError
			};

			FakeConnection() : state(Initial), delayConnect(false) {}

			virtual void listen() {
				assert(false);
			}

			void setError(const Error& e) {
				error = boost::optional<Error>(e);
				state = DisconnectedWithError;
				if (connectedTo) {
					MainEventLoop::postEvent(
							boost::bind(boost::ref(onDisconnected), error),
							shared_from_this());
				}
			}

			virtual void connect(const HostAddressPort& address) {
				if (delayConnect) {
					state = Connecting;
				}
				else {
					if (!error) {
						connectedTo = address;
						state = Connected;
					}
					else {
						state = DisconnectedWithError;
					}
					MainEventLoop::postEvent(
							boost::bind(boost::ref(onConnectFinished), error),
							shared_from_this());
				}
			}

			virtual void disconnect() {
				if (!error) {
					state = Disconnected;
				}
				else {
					state = DisconnectedWithError;
				}
				connectedTo.reset();
				MainEventLoop::postEvent(
						boost::bind(boost::ref(onDisconnected), error),
						shared_from_this());
			}

			virtual void write(const ByteArray& data) {
				dataWritten.push_back(data);
			}

			void setDelayConnect() {
				delayConnect = true;
			}

			boost::optional<HostAddressPort> connectedTo;
			std::vector<ByteArray> dataWritten;
			boost::optional<Error> error;
			State state;
			bool delayConnect;
	};
}
