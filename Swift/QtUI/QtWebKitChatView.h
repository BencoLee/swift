/*
 * Copyright (c) 2010-2013 Remko Tronçon
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#pragma once

#include <QString>
#include <QWidget>
#include <QList>
#include <QWebElement>

#include <boost/shared_ptr.hpp>

#include <Swiften/Base/Override.h>

#include <Swift/Controllers/UIInterfaces/ChatWindow.h>

#include <Swift/QtUI/ChatSnippet.h>
#include <Swift/QtUI/QtChatView.h>

class QWebPage;
class QUrl;
class QDate;

namespace Swift {
	class QtWebView;
	class QtChatTheme;
	class QtChatWindowJSBridge;
	class UIEventStream;
	class QtChatWindow;
	class QtWebKitChatView : public QtChatView {
			Q_OBJECT

		public:
			static const QString ButtonWhiteboardSessionCancel;
			static const QString ButtonWhiteboardSessionAcceptRequest;
			static const QString ButtonWhiteboardShowWindow;
			static const QString ButtonFileTransferCancel;
			static const QString ButtonFileTransferSetDescription;
			static const QString ButtonFileTransferSendRequest;
			static const QString ButtonFileTransferAcceptRequest;
			static const QString ButtonMUCInvite;
		public:
			QtWebKitChatView(QtChatWindow* window, UIEventStream* eventStream, QtChatTheme* theme, QWidget* parent, bool disableAutoScroll = false);
			~QtWebKitChatView();

			/** Add message to window.
			 * @return id of added message (for acks).
			 */
			virtual std::string addMessage(const ChatWindow::ChatMessage& message, const std::string& senderName, bool senderIsSelf, boost::shared_ptr<SecurityLabel> label, const std::string& avatarPath, const boost::posix_time::ptime& time, const HighlightAction& highlight) SWIFTEN_OVERRIDE;
			/** Adds action to window.
			 * @return id of added message (for acks);
			 */
			virtual std::string addAction(const ChatWindow::ChatMessage& message, const std::string& senderName, bool senderIsSelf, boost::shared_ptr<SecurityLabel> label, const std::string& avatarPath, const boost::posix_time::ptime& time, const HighlightAction& highlight) SWIFTEN_OVERRIDE;

			virtual void addSystemMessage(const ChatWindow::ChatMessage& message, ChatWindow::Direction direction) SWIFTEN_OVERRIDE;
			virtual void addPresenceMessage(const ChatWindow::ChatMessage& message, ChatWindow::Direction direction) SWIFTEN_OVERRIDE;

			virtual void addErrorMessage(const ChatWindow::ChatMessage& message) SWIFTEN_OVERRIDE;
			virtual void replaceMessage(const ChatWindow::ChatMessage& message, const std::string& id, const boost::posix_time::ptime& time, const HighlightAction& highlight) SWIFTEN_OVERRIDE;
			virtual void replaceWithAction(const ChatWindow::ChatMessage& message, const std::string& id, const boost::posix_time::ptime& time, const HighlightAction& highlight) SWIFTEN_OVERRIDE;
			void replaceLastMessage(const ChatWindow::ChatMessage& message);
			void setAckState(const std::string& id, ChatWindow::AckState state);
			
			virtual std::string addFileTransfer(const std::string& senderName, bool senderIsSelf, const std::string& filename, const boost::uintmax_t sizeInBytes) SWIFTEN_OVERRIDE;
			virtual void setFileTransferProgress(std::string, const int percentageDone) SWIFTEN_OVERRIDE;
			virtual void setFileTransferStatus(std::string, const ChatWindow::FileTransferState state, const std::string& msg = "") SWIFTEN_OVERRIDE;
			virtual void addMUCInvitation(const std::string& senderName, const JID& jid, const std::string& reason, const std::string& password, bool direct, bool isImpromptu, bool isContinuation) SWIFTEN_OVERRIDE;
			virtual std::string addWhiteboardRequest(const QString& contact, bool senderIsSelf) SWIFTEN_OVERRIDE;
			virtual void setWhiteboardSessionStatus(std::string id, const ChatWindow::WhiteboardSessionState state) SWIFTEN_OVERRIDE;
			virtual void setMessageReceiptState(const std::string& id, ChatWindow::ReceiptState state) SWIFTEN_OVERRIDE;

			virtual void showEmoticons(bool show) SWIFTEN_OVERRIDE;
			void addMessageTop(boost::shared_ptr<ChatSnippet> snippet);
			void addMessageBottom(boost::shared_ptr<ChatSnippet> snippet);

			int getSnippetPositionByDate(const QDate& date); // FIXME : This probably shouldn't have been public
			void addLastSeenLine();

		private: // previously public, now private
			void replaceLastMessage(const QString& newMessage);
			void replaceLastMessage(const QString& newMessage, const QString& note);
			void replaceMessage(const QString& newMessage, const QString& id, const QDateTime& time);
			void rememberScrolledToBottom();
			void setAckXML(const QString& id, const QString& xml);
			void setReceiptXML(const QString& id, const QString& xml);
			void displayReceiptInfo(const QString& id, bool showIt);

			QString getLastSentMessage();
			void addToJSEnvironment(const QString&, QObject*);
			void setFileTransferProgress(QString id, const int percentageDone);
			void setFileTransferStatus(QString id, const ChatWindow::FileTransferState state, const QString& msg);
			void setWhiteboardSessionStatus(QString id, const ChatWindow::WhiteboardSessionState state);
			void setMUCInvitationJoined(QString id);
			
		signals:
			void gotFocus();
			void fontResized(int);
			void logCleared();
			void scrollRequested(int pos);
			void scrollReachedTop();
			void scrollReachedBottom();

		public slots:
			void copySelectionToClipboard();
			void handleLinkClicked(const QUrl&);
			void resetView();
			void resetTopInsertPoint();
			void increaseFontSize(int numSteps = 1);
			void decreaseFontSize();
			void resizeFont(int fontSizeSteps);
			void scrollToBottom();
			void handleKeyPressEvent(QKeyEvent* event);

		private slots:
			void handleViewLoadFinished(bool);
			void handleFrameSizeChanged();
			void handleClearRequested();
			void handleScrollRequested(int dx, int dy, const QRect& rectToScroll);
			void handleHTMLButtonClicked(QString id, QString arg1, QString arg2, QString arg3, QString arg4, QString arg5);

		private:
			enum PreviousMessageKind {
				PreviosuMessageWasNone,
				PreviousMessageWasMessage,
				PreviousMessageWasSystem,
				PreviousMessageWasPresence,
				PreviousMessageWasFileTransfer,
				PreviousMessageWasMUCInvite
			};
			std::string addMessage(
					const QString& message, 
					const std::string& senderName, 
					bool senderIsSelf, 
					boost::shared_ptr<SecurityLabel> label, 
					const std::string& avatarPath, 
					const QString& style, 
					const boost::posix_time::ptime& time, 
					const HighlightAction& highlight,
					ChatSnippet::Direction direction);
			void replaceMessage(
					const QString& message, 
					const std::string& id, 
					const boost::posix_time::ptime& time, 
					const QString& style, 
					const HighlightAction& highlight);
			bool appendToPreviousCheck(PreviousMessageKind messageKind, const std::string& senderName, bool senderIsSelf);
			static ChatSnippet::Direction getActualDirection(const ChatWindow::ChatMessage& message, ChatWindow::Direction direction);
			QString chatMessageToHTML(const ChatWindow::ChatMessage& message);
			QString getHighlightSpanStart(const HighlightAction& highlight);
			static QString buildChatWindowButton(const QString& name, const QString& id, const QString& arg1 = QString(), const QString& arg2 = QString(), const QString& arg3 = QString(), const QString& arg4 = QString(), const QString& arg5 = QString());

		private:
			void headerEncode();
			void messageEncode();
			void addToDOM(boost::shared_ptr<ChatSnippet> snippet);
			QWebElement snippetToDOM(boost::shared_ptr<ChatSnippet> snippet);

			QtChatWindow* window_;
			UIEventStream* eventStream_;
			bool viewReady_;
			bool isAtBottom_;
			bool topMessageAdded_;
			int scrollBarMaximum_;
			QtWebView* webView_;
			QWebPage* webPage_;
			int fontSizeSteps_;
			QtChatTheme* theme_;
			QWebElement newInsertPoint_;
			QWebElement topInsertPoint_;
			QWebElement lineSeparator_;
			QWebElement lastElement_;
			QWebElement firstElement_;
			QWebElement document_;
			bool disableAutoScroll_;
			QtChatWindowJSBridge* jsBridge;
			PreviousMessageKind previousMessageKind_;
			bool previousMessageWasSelf_;
			bool showEmoticons_;
			bool insertingLastLine_;
			int idCounter_;
			QString previousSenderName_;
			std::map<QString, QString> descriptions_;
	};
}
