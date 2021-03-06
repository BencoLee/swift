/*
 * Copyright (c) 2013-2016 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#pragma once

#include <Swiften/Base/API.h>
#include <Swiften/Base/Override.h>
#include <Swiften/FileTransfer/FileTransferTransporterFactory.h>

namespace Swift {
    class SOCKS5BytestreamRegistry;
    class SOCKS5BytestreamServerManager;
    class SOCKS5BytestreamProxiesManager;
    class IDGenerator;
    class ConnectionFactory;
    class TimerFactory;
    class CryptoProvider;
    class IQRouter;

    class SWIFTEN_API DefaultFileTransferTransporterFactory : public FileTransferTransporterFactory {
        public:
            DefaultFileTransferTransporterFactory(
                SOCKS5BytestreamRegistry*,
                SOCKS5BytestreamServerManager* s5bServerManager,
                SOCKS5BytestreamProxiesManager* s5bProxy,
                IDGenerator* idGenerator,
                ConnectionFactory*,
                TimerFactory*,
                CryptoProvider*,
                IQRouter*);
            virtual ~DefaultFileTransferTransporterFactory();

            virtual FileTransferTransporter* createInitiatorTransporter(
                    const JID& initiator, const JID& responder, const FileTransferOptions&) SWIFTEN_OVERRIDE;
            virtual FileTransferTransporter* createResponderTransporter(
                    const JID& initiator, const JID& responder, const std::string& s5bSessionID, const FileTransferOptions&) SWIFTEN_OVERRIDE;

        private:
            SOCKS5BytestreamRegistry* s5bRegistry;
            SOCKS5BytestreamServerManager* s5bServerManager;
            SOCKS5BytestreamProxiesManager* s5bProxiesManager;
            IDGenerator* idGenerator;
            ConnectionFactory* connectionFactory;
            TimerFactory* timerFactory;
            CryptoProvider* cryptoProvider;
            IQRouter* iqRouter;
    };
}
