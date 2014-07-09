/*
 * Copyright (c) 2013 Tobias Markmann
 * Licensed under the simplified BSD license.
 * See Documentation/Licenses/BSD-simplified.txt for more information.
 */

/*
 * Copyright (c) 2014 Kevin Smith and Remko Tronçon
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#pragma once

#include <vector>

#include <QTreeView>

#include <Swift/Controllers/Contact.h>
#include <Swiften/Base/Log.h>

#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>

namespace Swift {

class ContactListDelegate;
class ContactListModel;
class SettingsProvider;
class QtRemovableItemDelegate;

class QtContactListWidget : public QTreeView {
	Q_OBJECT
public:
	QtContactListWidget(QWidget* parent, SettingsProvider* settings);
	virtual ~QtContactListWidget();

	void setList(const std::vector<Contact::ref>& list);
	std::vector<Contact::ref> getList() const;
	Contact::ref getContact(const size_t i);
	void setMaximumNoOfContactsToOne(bool limited);
	bool isFull() const;

public slots:
	void updateContacts(const std::vector<Contact::ref>& contactUpdates);

signals:
	void onListChanged(std::vector<Contact::ref> list);
	void onJIDsAdded(const std::vector<JID>& jids);

private:
	void handleSettingsChanged(const std::string&);

private:
	SettingsProvider* settings_;
	ContactListModel* contactListModel_;
	ContactListDelegate* contactListDelegate_;
	QtRemovableItemDelegate* removableItemDelegate_;
	bool limited_;
};

}
