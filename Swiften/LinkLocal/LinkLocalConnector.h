#pragma once

#include <boost/shared_ptr.hpp>
#include <boost/signal.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <vector>

#include "Swiften/Network/Connection.h"
#include "Swiften/LinkLocal/LinkLocalService.h"

namespace Swift {
	class ConnectionFactory;
	class HostAddress;
	class Element;
	class PayloadParserFactoryCollection;
	class PayloadSerializerCollection;
	class DNSSDQuerier;
	class DNSSDResolveHostnameQuery;

	class LinkLocalConnector : public boost::enable_shared_from_this<LinkLocalConnector> {
		public:
			LinkLocalConnector(
					const LinkLocalService& service, 
					boost::shared_ptr<DNSSDQuerier> querier,
					boost::shared_ptr<Connection> connection);
			~LinkLocalConnector();

			const LinkLocalService& getService() const {
				return service;
			}

			void connect();
			void cancel();
			void queueElement(boost::shared_ptr<Element> element);

			const std::vector<boost::shared_ptr<Element> >& getQueuedElements() const {
				return queuedElements;
			}

			boost::shared_ptr<Connection> getConnection() const {
				return connection;
			}

			boost::signal<void (bool)> onConnectFinished;

		private:
			void handleHostnameResolved(const boost::optional<HostAddress>& address);
			void handleConnected(bool error);

		private:
			LinkLocalService service;
			boost::shared_ptr<DNSSDQuerier> querier;
			boost::shared_ptr<DNSSDResolveHostnameQuery> resolveQuery;
			boost::shared_ptr<Connection> connection;
			std::vector<boost::shared_ptr<Element> > queuedElements;
	};
}
