/*
 * Copyright (c) 2012 Maciej Niedzielski
 * Licensed under the simplified BSD license.
 * See Documentation/Licenses/BSD-simplified.txt for more information.
 */

/*
 * Copyright (c) 2014 Kevin Smith and Remko Tronçon
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#pragma once

#include <boost/shared_ptr.hpp>

#include <Swift/Controllers/UIEvents/UIEvent.h>

namespace Swift {

	class UIEventStream;

	class HighlightEditorWindowFactory;
	class HighlightEditorWindow;

	class HighlightManager;
	class ContactSuggester;

	class HighlightEditorController {
		public:
			HighlightEditorController(UIEventStream* uiEventStream, HighlightEditorWindowFactory* highlightEditorWindowFactory, HighlightManager* highlightManager);
			~HighlightEditorController();

			HighlightManager* getHighlightManager() const { return highlightManager_; }
			void setContactSuggester(ContactSuggester *suggester) { contactSuggester_ = suggester; }

		private:
			void handleUIEvent(boost::shared_ptr<UIEvent> event);
			void handleContactSuggestionsRequested(const std::string& text);

		private:
			HighlightEditorWindowFactory* highlightEditorWindowFactory_;
			HighlightEditorWindow* highlightEditorWindow_;
			HighlightManager* highlightManager_;
			ContactSuggester* contactSuggester_;
	};

}
