/*
 * Copyright (c) 2010 Remko Tronçon
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#include <vector>
#include <openssl/err.h>
#include <openssl/pkcs12.h>

#include "Swiften/TLS/OpenSSL/OpenSSLContext.h"
#include "Swiften/TLS/PKCS12Certificate.h"

#pragma GCC diagnostic ignored "-Wold-style-cast"

namespace Swift {

static const int SSL_READ_BUFFERSIZE = 8192;

void freeX509Stack(STACK_OF(X509)* stack) {
	sk_X509_free(stack);
}

OpenSSLContext::OpenSSLContext() : state_(Start), context_(0), handle_(0), readBIO_(0), writeBIO_(0) {
	ensureLibraryInitialized();
	context_ = SSL_CTX_new(TLSv1_client_method());
}

OpenSSLContext::~OpenSSLContext() {
	SSL_free(handle_);
	SSL_CTX_free(context_);
}

void OpenSSLContext::ensureLibraryInitialized() {
	static bool isLibraryInitialized = false;
	if (!isLibraryInitialized) {
		SSL_load_error_strings();
		SSL_library_init();
		OpenSSL_add_all_algorithms();
		isLibraryInitialized = true;
	}
}

void OpenSSLContext::connect() {
	handle_ = SSL_new(context_);
	// Ownership of BIOs is ransferred
	readBIO_ = BIO_new(BIO_s_mem());
	writeBIO_ = BIO_new(BIO_s_mem());
	SSL_set_bio(handle_, readBIO_, writeBIO_);

	state_ = Connecting;
	doConnect();
}

void OpenSSLContext::doConnect() {
	int connectResult = SSL_connect(handle_);
	int error = SSL_get_error(handle_, connectResult);
	switch (error) {
		case SSL_ERROR_NONE:
			state_ = Connected;
			onConnected();
			//X509* x = SSL_get_peer_certificate(handle_);
			//std::cout << x->name << std::endl;
			//const char* comp = SSL_get_current_compression(handle_);
			//std::cout << "Compression: " << SSL_COMP_get_name(comp) << std::endl;
			break;
		case SSL_ERROR_WANT_READ:
			sendPendingDataToNetwork();
			break;
		default:
			state_ = Error;
			onError();
	}
}

void OpenSSLContext::sendPendingDataToNetwork() {
	int size = BIO_pending(writeBIO_);
	if (size > 0) {
		ByteArray data;
		data.resize(size);
		BIO_read(writeBIO_, data.getData(), size);
		onDataForNetwork(data);
	}
}

void OpenSSLContext::handleDataFromNetwork(const ByteArray& data) {
	BIO_write(readBIO_, data.getData(), data.getSize());
	switch (state_) {
		case Connecting:
			doConnect();
			break;
		case Connected:
			sendPendingDataToApplication();
			break;
		case Start: assert(false); break;
		case Error: /*assert(false);*/ break;
	}
}

void OpenSSLContext::handleDataFromApplication(const ByteArray& data) {
	if (SSL_write(handle_, data.getData(), data.getSize()) >= 0) {
		sendPendingDataToNetwork();
	}
	else {
		state_ = Error;
		onError();
	}
}

void OpenSSLContext::sendPendingDataToApplication() {
	ByteArray data;
	data.resize(SSL_READ_BUFFERSIZE);
	int ret = SSL_read(handle_, data.getData(), data.getSize());
	while (ret > 0) {
		data.resize(ret);
		onDataForApplication(data);
		data.resize(SSL_READ_BUFFERSIZE);
		ret = SSL_read(handle_, data.getData(), data.getSize());
	}
	if (ret < 0 && SSL_get_error(handle_, ret) != SSL_ERROR_WANT_READ) {
		state_ = Error;
		onError();
	}
}

bool OpenSSLContext::setClientCertificate(const PKCS12Certificate& certificate) {
	if (certificate.isNull()) {
		return false;
	}

	// Create a PKCS12 structure
	BIO* bio = BIO_new(BIO_s_mem());
	BIO_write(bio, certificate.getData().getData(), certificate.getData().getSize());
	boost::shared_ptr<PKCS12> pkcs12(d2i_PKCS12_bio(bio, NULL), PKCS12_free);
	BIO_free(bio);
	if (!pkcs12) {
		return false;
	}

	// Parse PKCS12
	X509 *certPtr = 0;
	EVP_PKEY* privateKeyPtr = 0;
	STACK_OF(X509)* caCertsPtr = 0;
	int result = PKCS12_parse(pkcs12.get(), certificate.getPassword().getUTF8Data(), &privateKeyPtr, &certPtr, &caCertsPtr);
	if (result != 1) { 
		return false;
	}
	boost::shared_ptr<X509> cert(certPtr, X509_free);
	boost::shared_ptr<EVP_PKEY> privateKey(privateKeyPtr, EVP_PKEY_free);
	boost::shared_ptr<STACK_OF(X509)> caCerts(caCertsPtr, freeX509Stack);

	// Use the key & certificates
	if (SSL_CTX_use_certificate(context_, cert.get()) != 1) {
		return false;
	}
	if (SSL_CTX_use_PrivateKey(context_, privateKey.get()) != 1) {
		return false;
	}
	for (int i = 0;  i < sk_X509_num(caCerts.get()); ++i) {
		SSL_CTX_add_extra_chain_cert(context_, sk_X509_value(caCerts.get(), i));
	}
	return true;
}

}
