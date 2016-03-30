/*
 * Copyright (c) 2010-2016 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#include <Limber/Server/ServerFromClientSession.h>

#include <boost/bind.hpp>
#include <boost/smart_ptr/make_shared.hpp>

#include <Swiften/Elements/AuthFailure.h>
#include <Swiften/Elements/AuthRequest.h>
#include <Swiften/Elements/AuthSuccess.h>
#include <Swiften/Elements/IQ.h>
#include <Swiften/Elements/ProtocolHeader.h>
#include <Swiften/Elements/ResourceBind.h>
#include <Swiften/Elements/StartSession.h>
#include <Swiften/Elements/StreamFeatures.h>
#include <Swiften/Network/Connection.h>
#include <Swiften/SASL/PLAINMessage.h>
#include <Swiften/StreamStack/XMPPLayer.h>

#include <Limber/Server/UserRegistry.h>

namespace Swift {

ServerFromClientSession::ServerFromClientSession(
		const std::string& id,
		boost::shared_ptr<Connection> connection, 
		PayloadParserFactoryCollection* payloadParserFactories, 
		PayloadSerializerCollection* payloadSerializers,
		XMLParserFactory* xmlParserFactory,
		UserRegistry* userRegistry) : 
			Session(connection, payloadParserFactories, payloadSerializers, xmlParserFactory),
			id_(id),
			userRegistry_(userRegistry),
			authenticated_(false),
			initialized(false),
			allowSASLEXTERNAL(false) {
}


void ServerFromClientSession::handleElement(boost::shared_ptr<ToplevelElement> element) {
	if (isInitialized()) {
		onElementReceived(element);
	}
	else {
		if (AuthRequest* authRequest = dynamic_cast<AuthRequest*>(element.get())) {
			if (authRequest->getMechanism() == "PLAIN" || (allowSASLEXTERNAL && authRequest->getMechanism() == "EXTERNAL")) {
				if (authRequest->getMechanism() == "EXTERNAL") {
						getXMPPLayer()->writeElement(boost::make_shared<AuthSuccess>());
						authenticated_ = true;
						getXMPPLayer()->resetParser();
				}
				else {
					PLAINMessage plainMessage(authRequest->getMessage() ? *authRequest->getMessage() : createSafeByteArray(""));
					if (userRegistry_->isValidUserPassword(JID(plainMessage.getAuthenticationID(), getLocalJID().getDomain()), plainMessage.getPassword())) {
						getXMPPLayer()->writeElement(boost::make_shared<AuthSuccess>());
						user_ = plainMessage.getAuthenticationID();
						authenticated_ = true;
						getXMPPLayer()->resetParser();
					}
					else {
						getXMPPLayer()->writeElement(boost::shared_ptr<AuthFailure>(new AuthFailure));
						finishSession(AuthenticationFailedError);
					}
				}
			}
			else {
				getXMPPLayer()->writeElement(boost::shared_ptr<AuthFailure>(new AuthFailure));
				finishSession(NoSupportedAuthMechanismsError);
			}
		}
		else if (IQ* iq = dynamic_cast<IQ*>(element.get())) {
			if (boost::shared_ptr<ResourceBind> resourceBind = iq->getPayload<ResourceBind>()) {
				setRemoteJID(JID(user_, getLocalJID().getDomain(), resourceBind->getResource()));
				boost::shared_ptr<ResourceBind> resultResourceBind(new ResourceBind());
				resultResourceBind->setJID(getRemoteJID());
				getXMPPLayer()->writeElement(IQ::createResult(JID(), iq->getID(), resultResourceBind));
			}
			else if (iq->getPayload<StartSession>()) {
				getXMPPLayer()->writeElement(IQ::createResult(getRemoteJID(), iq->getID()));
				setInitialized();
			}
		}
	}
}

void ServerFromClientSession::handleStreamStart(const ProtocolHeader& incomingHeader) {
	setLocalJID(JID("", incomingHeader.getTo()));
	ProtocolHeader header;
	header.setFrom(incomingHeader.getTo());
	header.setID(id_);
	getXMPPLayer()->writeHeader(header);

	boost::shared_ptr<StreamFeatures> features(new StreamFeatures());
	if (!authenticated_) {
		features->addAuthenticationMechanism("PLAIN");
		if (allowSASLEXTERNAL) {
			features->addAuthenticationMechanism("EXTERNAL");
		}
	}
	else {
		features->setHasResourceBind();
		features->setHasSession();
	}
	getXMPPLayer()->writeElement(features);
}

void ServerFromClientSession::setInitialized() {
	initialized = true;
	onSessionStarted();
}

void ServerFromClientSession::setAllowSASLEXTERNAL() {
	allowSASLEXTERNAL = true;
}

}
