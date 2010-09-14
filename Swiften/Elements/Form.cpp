/*
 * Copyright (c) 2010 Remko Tronçon
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#include "Swiften/Elements/Form.h"
#include "Swiften/Base/foreach.h"

namespace Swift {

String Form::getFormType() const {
	foreach(FormField::ref field, fields_) {
		boost::shared_ptr<HiddenFormField> f = boost::dynamic_pointer_cast<HiddenFormField>(field);
		if (f && f->getName() == "FORM_TYPE") {
			return f->getValue();
		}
	}
	return "";
}

}
