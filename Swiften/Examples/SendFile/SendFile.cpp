/*
 * Copyright (c) 2010 Remko Tronçon
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#include <boost/bind.hpp>
#include <boost/filesystem.hpp>

#include "Swiften/Client/Client.h"
#include "Swiften/Network/BoostTimer.h"
#include "Swiften/EventLoop/EventLoop.h"
#include "Swiften/Client/ClientXMLTracer.h"
#include "Swiften/EventLoop/SimpleEventLoop.h"
#include "Swiften/Network/MainBoostIOServiceThread.h"
#include "Swiften/FileTransfer/OutgoingFileTransfer.h"
#include "Swiften/FileTransfer/FileReadBytestream.h"
#include "Swiften/FileTransfer/SOCKS5BytestreamServer.h"
#include "Swiften/Network/BoostConnectionServer.h"
#include "Swiften/Network/BoostIOServiceThread.h"

using namespace Swift;

SimpleEventLoop eventLoop;
int exitCode = 2;

class FileSender {
	public:
		FileSender(const JID& jid, const String& password, const JID& recipient, const boost::filesystem::path& file, int port) : jid(jid), password(password), recipient(recipient), file(file), transfer(NULL) {
			connectionServer = BoostConnectionServer::create(port, &MainBoostIOServiceThread::getInstance().getIOService(), &eventLoop);
			socksBytestreamServer = new SOCKS5BytestreamServer(connectionServer);

			client = new Swift::Client(&eventLoop, jid, password);
			client->onConnected.connect(boost::bind(&FileSender::handleConnected, this));
			client->onError.connect(boost::bind(&FileSender::handleError, this, _1));
			//tracer = new ClientXMLTracer(client);
		}

		~FileSender() {
			//delete tracer;
			client->onError.disconnect(boost::bind(&FileSender::handleError, this, _1));
			client->onConnected.disconnect(boost::bind(&FileSender::handleConnected, this));
			delete client;
			delete socksBytestreamServer;
		}

		void start() {
			connectionServer->start();
			socksBytestreamServer->start();
			client->connect();
		}

		void stop() {
			if (transfer) {
				transfer->stop();
			}
			client->disconnect();
			socksBytestreamServer->stop();
			connectionServer->stop();
		}

	private:
		void handleConnected() {
			client->sendPresence(Presence::create());
			transfer = new OutgoingFileTransfer("myid",	client->getJID(), recipient, file.filename(), boost::filesystem::file_size(file), "A file", boost::shared_ptr<FileReadBytestream>(new FileReadBytestream(file)), client->getIQRouter(), socksBytestreamServer);
			transfer->onFinished.connect(boost::bind(&FileSender::handleFileTransferFinished, this, _1));
			transfer->start();
		}

		void handleError(const ClientError&) {
			std::cerr << "Error!" << std::endl;
			exit(-1);
		}

		void handleFileTransferFinished(const boost::optional<FileTransferError>& error) {
			std::cout << "File transfer finished" << std::endl;
			if (error) {
				exit(-1);
			}
			else {
				exit(0);
			}
		}

		void exit(int code) {
			exitCode = code;
			stop();
			eventLoop.stop();
		}
	
	private:
		BoostConnectionServer::ref connectionServer;
		SOCKS5BytestreamServer* socksBytestreamServer;
		JID jid;
		String password;
		JID recipient;
		boost::filesystem::path file;
		Client* client;
		ClientXMLTracer* tracer;
		OutgoingFileTransfer* transfer;
};


int main(int argc, char* argv[]) {
	if (argc != 5) {
		std::cerr << "Usage: " << argv[0] << " <jid> <password> <recipient> <file>" << std::endl;
		return -1;
	}

	JID sender(argv[1]);
	JID recipient(argv[3]);
	FileSender fileSender(sender, String(argv[2]), recipient, boost::filesystem::path(argv[4]), 8888);
	fileSender.start();

	{
		/*BoostTimer::ref timer(BoostTimer::create(30000, &MainBoostIOServiceThread::getInstance().getIOService()));
		timer->onTick.connect(boost::bind(&SimpleEventLoop::stop, &eventLoop));
		timer->start();*/

		eventLoop.run();
	}

	return exitCode;
}
