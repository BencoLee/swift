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

#pragma once

#include <boost/shared_ptr.hpp>
#include <boost/optional/optional.hpp>

#include <Swiften/Base/API.h>
#include <Swiften/Base/Override.h>
#include <Swiften/Jingle/JingleContentID.h>
#include <Swiften/Elements/StreamInitiationFileInfo.h>
#include <Swiften/FileTransfer/OutgoingFileTransfer.h>
#include <Swiften/FileTransfer/JingleFileTransfer.h>
#include <Swiften/FileTransfer/FileTransferOptions.h>

namespace Swift {
	class ReadBytestream;
	class IDGenerator;
	class IncrementalBytestreamHashCalculator;
	class CryptoProvider;
	class FileTransferTransporter;
	class FileTransferTransporterFactory;
	class TransportSession;

	class SWIFTEN_API OutgoingJingleFileTransfer : public OutgoingFileTransfer, public JingleFileTransfer {
		public:
			OutgoingJingleFileTransfer(
				const JID& to,
				boost::shared_ptr<JingleSession>,
				boost::shared_ptr<ReadBytestream>,
				FileTransferTransporterFactory*,
				IDGenerator*,
				const StreamInitiationFileInfo&,
				const FileTransferOptions&,
				CryptoProvider*);
			virtual ~OutgoingJingleFileTransfer();
			
			void start();
			void cancel();

		private:
			enum State {
				Initial,
				GeneratingInitialLocalCandidates,	
				WaitingForAccept,
				TryingCandidates,
				WaitingForPeerProxyActivate,
				WaitingForLocalProxyActivate,
				WaitingForCandidateAcknowledge,
				FallbackRequested,
				Transferring,
				Finished
			};

			virtual void handleSessionAcceptReceived(const JingleContentID&, boost::shared_ptr<JingleDescription>, boost::shared_ptr<JingleTransportPayload>) SWIFTEN_OVERRIDE;
			virtual void handleSessionTerminateReceived(boost::optional<JinglePayload::Reason> reason) SWIFTEN_OVERRIDE;
			virtual void handleTransportAcceptReceived(const JingleContentID&, boost::shared_ptr<JingleTransportPayload>) SWIFTEN_OVERRIDE;
			void startTransferViaRemoteCandidate();
			void startTransferViaLocalCandidate();
			void startTransferringIfCandidateAcknowledged();

			virtual void handleLocalTransportCandidatesGenerated(const std::string& s5bSessionID, const std::vector<JingleS5BTransportPayload::Candidate>&) SWIFTEN_OVERRIDE;
			virtual void handleTransportInfoAcknowledged(const std::string& id) SWIFTEN_OVERRIDE;

			virtual JingleContentID getContentID() const SWIFTEN_OVERRIDE;

			virtual void terminate(JinglePayload::Reason::Type reason) SWIFTEN_OVERRIDE;

			virtual void fallback() SWIFTEN_OVERRIDE;
			void handleTransferFinished(boost::optional<FileTransferError>);

			void sendSessionInfoHash();

			virtual void startTransferring(boost::shared_ptr<TransportSession>) SWIFTEN_OVERRIDE;

			virtual bool hasPriorityOnCandidateTie() const SWIFTEN_OVERRIDE;
			virtual bool isWaitingForPeerProxyActivate() const SWIFTEN_OVERRIDE;
			virtual bool isWaitingForLocalProxyActivate() const SWIFTEN_OVERRIDE;
			virtual bool isTryingCandidates() const SWIFTEN_OVERRIDE;
			virtual boost::shared_ptr<TransportSession> createLocalCandidateSession() SWIFTEN_OVERRIDE;
			virtual boost::shared_ptr<TransportSession> createRemoteCandidateSession() SWIFTEN_OVERRIDE;

			void stopAll();
			void setState(State state);
			void setFinishedState(FileTransfer::State::Type, const boost::optional<FileTransferError>& error);

			static FileTransfer::State::Type getExternalState(State state);

		private:
			IDGenerator* idGenerator;
			boost::shared_ptr<ReadBytestream> stream;
			StreamInitiationFileInfo fileInfo;
			FileTransferOptions options;
			JingleContentID contentID;
			IncrementalBytestreamHashCalculator* hashCalculator;
			State state;
			bool candidateAcknowledged;

			boost::bsignals::connection processedBytesConnection;
			boost::bsignals::connection transferFinishedConnection;
	};

}
