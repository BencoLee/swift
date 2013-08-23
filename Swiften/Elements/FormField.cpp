/*
 * Copyright (c) 2013 Remko Tronçon
 * Licensed under the GNU General Public License.
 * See the COPYING file for more information.
 */

#include <Swiften/Elements/FormField.h>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/algorithm/string/classification.hpp>

using namespace Swift;

FormField::~FormField() {
}

std::string FormField::getTextMultiValue() const {
	assert(type == TextMultiType || type == UnknownType);
	return boost::algorithm::join(values, "\n");
}

void FormField::setTextMultiValue(const std::string& value) {
	assert(type == TextMultiType || type == UnknownType);
	values.clear();
	boost::split(values, value, boost::is_any_of("\n"));
}

void FormField::setBoolValue(bool b) {
	assert(type == BooleanType || type == UnknownType);
	values.clear();
	values.push_back(b ? "1" : "0");
}
