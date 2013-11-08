/*
 * Copyright (c) 2013 Kevin Smith
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#pragma once

#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <QWidget>

#include <Swift/Controllers/UIInterfaces/ChatWindow.h>

#include <Swift/QtUI/QtChatView.h>

class QTextEdit;

namespace Swift {
	class HighlightAction;
	class SecurityLabel;

	class QtPlainChatView : public QtChatView {
		Q_OBJECT
		public:
			QtPlainChatView(QWidget* parent);
			virtual ~QtPlainChatView();

			/** Add message to window.
			 * @return id of added message (for acks).
			 */
			virtual std::string addMessage(const ChatWindow::ChatMessage& /*message*/, const std::string& /*senderName*/, bool /*senderIsSelf*/, boost::shared_ptr<SecurityLabel> /*label*/, const std::string& /*avatarPath*/, const boost::posix_time::ptime& /*time*/, const HighlightAction& /*highlight*/);
			/** Adds action to window.
			 * @return id of added message (for acks);
			 */
			virtual std::string addAction(const ChatWindow::ChatMessage& /*message*/, const std::string& /*senderName*/, bool /*senderIsSelf*/, boost::shared_ptr<SecurityLabel> /*label*/, const std::string& /*avatarPath*/, const boost::posix_time::ptime& /*time*/, const HighlightAction& /*highlight*/);

			virtual void addSystemMessage(const ChatWindow::ChatMessage& /*message*/, ChatWindow::Direction /*direction*/) {};
			virtual void addPresenceMessage(const ChatWindow::ChatMessage& /*message*/, ChatWindow::Direction /*direction*/) {};

			virtual void addErrorMessage(const ChatWindow::ChatMessage& /*message*/) {};
			virtual void replaceMessage(const ChatWindow::ChatMessage& /*message*/, const std::string& /*id*/, const boost::posix_time::ptime& /*time*/, const HighlightAction& /*highlight*/) {};
			virtual void replaceWithAction(const ChatWindow::ChatMessage& /*message*/, const std::string& /*id*/, const boost::posix_time::ptime& /*time*/, const HighlightAction& /*highlight*/) {};
			virtual void replaceLastMessage(const ChatWindow::ChatMessage& /*message*/) {};
			virtual void setAckState(const std::string& /*id*/, ChatWindow::AckState /*state*/) {};
			
			virtual std::string addFileTransfer(const std::string& /*senderName*/, bool /*senderIsSelf*/, const std::string& /*filename*/, const boost::uintmax_t /*sizeInBytes*/) {return "";};
			virtual void setFileTransferProgress(std::string, const int /*percentageDone*/) {};
			virtual void setFileTransferStatus(std::string, const ChatWindow::FileTransferState /*state*/, const std::string& /*msg*/ = "") {};
			virtual void addMUCInvitation(const std::string& /*senderName*/, const JID& /*jid*/, const std::string& /*reason*/, const std::string& /*password*/, bool /*direct*/, bool /*isImpromptu*/, bool /*isContinuation*/) {};
			virtual std::string addWhiteboardRequest(const QString& /*contact*/, bool /*senderIsSelf*/) {return "";};
			virtual void setWhiteboardSessionStatus(const std::string& /*id*/, const ChatWindow::WhiteboardSessionState /*state*/) {};
			virtual void setMessageReceiptState(const std::string& /*id*/, ChatWindow::ReceiptState /*state*/) {};

			virtual void showEmoticons(bool /*show*/) {};
			virtual void addLastSeenLine() {};

		public slots:
			virtual void resizeFont(int /*fontSizeSteps*/) {};
			virtual void scrollToBottom() {};
			virtual void handleKeyPressEvent(QKeyEvent* /*event*/) {};

		private:
			QTextEdit* log_;

	};
}
