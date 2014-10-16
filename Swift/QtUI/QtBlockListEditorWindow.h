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

#include <Swift/Controllers/UIInterfaces/BlockListEditorWidget.h>
#include <Swift/QtUI/QtVCardWidget/QtRemovableItemDelegate.h>

#include <QWidget>
#include <QTreeWidgetItem>

namespace Ui {
	class QtBlockListEditorWindow;
}

namespace Swift {

class QtJIDValidatedItemDelegate;

class QtBlockListEditorWindow : public QWidget, public BlockListEditorWidget {
	Q_OBJECT

	public:
		QtBlockListEditorWindow();
		virtual ~QtBlockListEditorWindow();

		virtual void show();
		virtual void hide();
		virtual void setCurrentBlockList(const std::vector<JID>& blockedJIDs);
		virtual void setBusy(bool isBusy);
		virtual void setError(const std::string& error);
		virtual std::vector<JID> getCurrentBlockList() const;
		virtual bool eventFilter(QObject* target, QEvent* event);

	private slots:
		void handleItemChanged(QTreeWidgetItem*, int);
		void applyChanges();

	private:
		Ui::QtBlockListEditorWindow* ui;
		QtRemovableItemDelegate* removeItemDelegate;
		QtJIDValidatedItemDelegate* editItemDelegate;
		QString freshBlockListTemplate;
};

}
