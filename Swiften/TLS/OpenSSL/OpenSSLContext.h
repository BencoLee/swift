#include <openssl/ssl.h>
#include <boost/signal.hpp>
#include <boost/noncopyable.hpp>

#include "Swiften/Base/ByteArray.h"

namespace Swift {
	class PKCS12Certificate;

	class OpenSSLContext : boost::noncopyable {
		public:
			OpenSSLContext();
			~OpenSSLContext();

			void connect();
			bool setClientCertificate(const PKCS12Certificate& cert);

			void handleDataFromNetwork(const ByteArray&);
			void handleDataFromApplication(const ByteArray&);

		public:
			boost::signal<void (const ByteArray&)> onDataForNetwork;
			boost::signal<void (const ByteArray&)> onDataForApplication;
			boost::signal<void ()> onError;
			boost::signal<void ()> onConnected;

		private:
			static void ensureLibraryInitialized();	

			void doConnect();
			void sendPendingDataToNetwork();
			void sendPendingDataToApplication();

		private:
			enum State { Start, Connecting, Connected, Error };

			State state_;
			SSL_CTX* context_;
			SSL* handle_;
			BIO* readBIO_;
			BIO* writeBIO_;
	};
}
