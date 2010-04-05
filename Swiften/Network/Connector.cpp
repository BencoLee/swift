#include "Swiften/Network/Connector.h"

#include <boost/bind.hpp>
#include <iostream>

#include "Swiften/Network/ConnectionFactory.h"
#include "Swiften/Network/DomainNameResolver.h"
#include "Swiften/Network/DomainNameAddressQuery.h"
#include "Swiften/Network/TimerFactory.h"

namespace Swift {

Connector::Connector(const String& hostname, DomainNameResolver* resolver, ConnectionFactory* connectionFactory, TimerFactory* timerFactory) : hostname(hostname), resolver(resolver), connectionFactory(connectionFactory), timerFactory(timerFactory), timeoutMilliseconds(0), queriedAllHosts(true) {
}

void Connector::setTimeoutMilliseconds(int milliseconds) {
	timeoutMilliseconds = milliseconds;
}

void Connector::start() {
	//std::cout << "Connector::start()" << std::endl;
	assert(!currentConnection);
	assert(!serviceQuery);
	assert(!timer);
	queriedAllHosts = false;
	serviceQuery = resolver->createServiceQuery("_xmpp-client._tcp." + hostname);
	serviceQuery->onResult.connect(boost::bind(&Connector::handleServiceQueryResult, this, _1));
	if (timeoutMilliseconds > 0) {
		timer = timerFactory->createTimer(timeoutMilliseconds);
		timer->onTick.connect(boost::bind(&Connector::handleTimeout, this));
		timer->start();
	}
	serviceQuery->run();
}

void Connector::queryAddress(const String& hostname) {
	assert(!addressQuery);
	addressQuery = resolver->createAddressQuery(hostname);
	addressQuery->onResult.connect(boost::bind(&Connector::handleAddressQueryResult, this, _1, _2));
	addressQuery->run();
}

void Connector::handleServiceQueryResult(const std::vector<DomainNameServiceQuery::Result>& result) {
	//std::cout << "Received SRV results" << std::endl;
	serviceQueryResults = std::deque<DomainNameServiceQuery::Result>(result.begin(), result.end());
	serviceQuery.reset();
	tryNextHostname();
}

void Connector::tryNextHostname() {
	if (queriedAllHosts) {
		//std::cout << "Connector::tryNextHostName(): Queried all hosts. Error." << std::endl;
		finish(boost::shared_ptr<Connection>());
	}
	else if (serviceQueryResults.empty()) {
		//std::cout << "Connector::tryNextHostName(): Falling back on A resolution" << std::endl;
		// Fall back on simple address resolving
		queriedAllHosts = true;
		queryAddress(hostname);
	}
	else {
		//std::cout << "Connector::tryNextHostName(): Querying next address" << std::endl;
		queryAddress(serviceQueryResults.front().hostname);
	}
}

void Connector::handleAddressQueryResult(const std::vector<HostAddress>& addresses, boost::optional<DomainNameResolveError> error) {
	//std::cout << "Connector::handleAddressQueryResult(): Start" << std::endl;
	addressQuery.reset();
	if (!serviceQueryResults.empty()) {
		DomainNameServiceQuery::Result serviceQueryResult = serviceQueryResults.front();
		serviceQueryResults.pop_front();
		if (error || addresses.empty()) {
			//std::cout << "Connector::handleAddressQueryResult(): A lookup for SRV host " << serviceQueryResult.hostname << " failed." << std::endl;
			tryNextHostname();
		}
		else {
			//std::cout << "Connector::handleAddressQueryResult(): A lookup for SRV host " << serviceQueryResult.hostname << " succeeded: " << address.toString() << std::endl;
			tryConnect(HostAddressPort(addresses[0], serviceQueryResult.port));
		}
	}
	else if (error || addresses.empty()) {
		//std::cout << "Connector::handleAddressQueryResult(): Fallback address query failed. Giving up" << std::endl;
		// The fallback address query failed
		assert(queriedAllHosts);
		finish(boost::shared_ptr<Connection>());
	}
	else {
		//std::cout << "Connector::handleAddressQueryResult(): Fallback address query succeeded: " << address.toString() << std::endl;
		// The fallback query succeeded
		tryConnect(HostAddressPort(addresses[0], 5222));
	}
}

void Connector::tryConnect(const HostAddressPort& target) {
	assert(!currentConnection);
	//std::cout << "Connector::tryConnect() " << target.getAddress().toString() << " " << target.getPort() << std::endl;
	currentConnection = connectionFactory->createConnection();
	currentConnection->onConnectFinished.connect(boost::bind(&Connector::handleConnectionConnectFinished, this, _1));
	currentConnection->connect(target);
}

void Connector::handleConnectionConnectFinished(bool error) {
	//std::cout << "Connector::handleConnectionConnectFinished() " << error << std::endl;
	if (error) {
		currentConnection.reset();
		tryNextHostname();
	}
	else {
		finish(currentConnection);
	}
}

void Connector::finish(boost::shared_ptr<Connection> connection) {
	if (timer) {
		timer->stop();
		timer.reset();
	}
	onConnectFinished(connection);
}

void Connector::handleTimeout() {
	finish(boost::shared_ptr<Connection>());
}

};
