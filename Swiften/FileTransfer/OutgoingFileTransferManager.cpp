/*
 * Copyright (c) 2011 Tobias Markmann
 * Licensed under the simplified BSD license.
 * See Documentation/Licenses/BSD-simplified.txt for more information.
 */

/*
 * Copyright (c) 2013 Remko Tronçon
 * Licensed under the GNU General Public License.
 * See the COPYING file for more information.
 */

#include "OutgoingFileTransferManager.h"

#include <boost/smart_ptr/make_shared.hpp>

#include <Swiften/JID/JID.h>
#include <Swiften/Jingle/JingleSessionManager.h>
#include <Swiften/Jingle/JingleSessionImpl.h>
#include <Swiften/Jingle/JingleContentID.h>
#include <Swiften/FileTransfer/OutgoingJingleFileTransfer.h>
#include <Swiften/Base/IDGenerator.h>

namespace Swift {

OutgoingFileTransferManager::OutgoingFileTransferManager(JingleSessionManager* jingleSessionManager, IQRouter* router, EntityCapsProvider* capsProvider, RemoteJingleTransportCandidateSelectorFactory* remoteFactory, LocalJingleTransportCandidateGeneratorFactory* localFactory, SOCKS5BytestreamRegistry* bytestreamRegistry, SOCKS5BytestreamProxy* bytestreamProxy, CryptoProvider* crypto) : jsManager(jingleSessionManager), iqRouter(router), capsProvider(capsProvider), remoteFactory(remoteFactory), localFactory(localFactory), bytestreamRegistry(bytestreamRegistry), bytestreamProxy(bytestreamProxy), crypto(crypto) {
	idGenerator = new IDGenerator();
}

OutgoingFileTransferManager::~OutgoingFileTransferManager() {
	delete idGenerator;
}

boost::shared_ptr<OutgoingFileTransfer> OutgoingFileTransferManager::createOutgoingFileTransfer(const JID& from, const JID& receipient, boost::shared_ptr<ReadBytestream> readBytestream, const StreamInitiationFileInfo& fileInfo) {
	// check if receipient support Jingle FT
	
	
	JingleSessionImpl::ref jingleSession = boost::make_shared<JingleSessionImpl>(from, receipient, idGenerator->generateID(), iqRouter);
	
	//jsManager->getSession(receipient, idGenerator->generateID());
	assert(jingleSession);
	jsManager->registerOutgoingSession(from, jingleSession);
	boost::shared_ptr<OutgoingJingleFileTransfer> jingleFT =  boost::shared_ptr<OutgoingJingleFileTransfer>(new OutgoingJingleFileTransfer(jingleSession, remoteFactory, localFactory, iqRouter, idGenerator, from, receipient, readBytestream, fileInfo, bytestreamRegistry, bytestreamProxy, crypto));
	
	// otherwise try SI
	
	// else fail
	
	return jingleFT;
}

}
