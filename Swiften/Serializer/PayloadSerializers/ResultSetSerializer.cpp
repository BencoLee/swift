/*
 * Copyright (c) 2014-2016 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#include <Swiften/Serializer/PayloadSerializers/ResultSetSerializer.h>

#include <boost/lexical_cast.hpp>
#include <boost/smart_ptr/make_shared.hpp>

#include <Swiften/Serializer/XML/XMLElement.h>
#include <Swiften/Serializer/XML/XMLRawTextNode.h>

using namespace Swift;

ResultSetSerializer::ResultSetSerializer() {
}

ResultSetSerializer::~ResultSetSerializer() {
}

std::string ResultSetSerializer::serializePayload(boost::shared_ptr<ResultSet> payload) const {
    if (!payload) {
        return "";
    }

    XMLElement element("set", "http://jabber.org/protocol/rsm");

    if (payload->getMaxItems()) {
        element.addNode(boost::make_shared<XMLElement>("max", "", boost::lexical_cast<std::string>(*payload->getMaxItems())));
    }

    if (payload->getCount()) {
        element.addNode(boost::make_shared<XMLElement>("count", "", boost::lexical_cast<std::string>(*payload->getCount())));
    }

    if (payload->getIndex()) {
        element.addNode(boost::make_shared<XMLElement>("index", "", boost::lexical_cast<std::string>(*payload->getIndex())));
    }

    if (payload->getFirstID()) {
        boost::shared_ptr<XMLElement> firstElement = boost::make_shared<XMLElement>("first", "", *payload->getFirstID());
        if (payload->getFirstIDIndex()) {
            firstElement->setAttribute("index", boost::lexical_cast<std::string>(*payload->getFirstIDIndex()));
        }
        element.addNode(firstElement);
    }

    if (payload->getLastID()) {
        element.addNode(boost::make_shared<XMLElement>("last", "", *payload->getLastID()));
    }

    if (payload->getBefore()) {
        element.addNode(boost::make_shared<XMLElement>("before", "", *payload->getBefore()));
    }

    if (payload->getAfter()) {
        element.addNode(boost::make_shared<XMLElement>("after", "", *payload->getAfter()));
    }

    return element.serialize();
}
