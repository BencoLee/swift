#ifndef SWIFTEN_MockTreeWidgetItem_H
#define SWIFTEN_MockTreeWidgetItem_H

#include "Swiften/Base/String.h"
#include "Swiften/Roster/TreeWidgetItem.h"

#include <boost/signal.hpp>
#include <boost/shared_ptr.hpp>

namespace Swift {

class MockTreeWidgetItem : public TreeWidgetItem {
	public:
		virtual ~MockTreeWidgetItem() {};
		virtual void setText(const String& text) {text_ = text;};
		String getText() {return text_;};
		virtual void setStatusText(const String&) {};
		virtual void setAvatarPath(const String&) {};
		virtual void setExpanded(bool) {};
		virtual void setStatusShow(StatusShow::Type /*show*/) {};
		virtual void show() {};
		virtual void hide() {};
	private:
		String text_;
};

}
#endif


