/*
 * Copyright (c) 2011 Tobias Markmann
 * Licensed under the simplified BSD license.
 * See Documentation/Licenses/BSD-simplified.txt for more information.
 */

/*
 * Copyright (c) 2014-2016 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#pragma once

#include <sstream>
#include <stack>
#include <string>

#include <boost/signals2.hpp>

#include <Swiften/Base/API.h>
#include <Swiften/Parser/XMLParser.h>
#include <Swiften/Parser/XMLParserClient.h>
#include <Swiften/Parser/XMLParserFactory.h>

namespace Swift {

class SWIFTEN_API XMLBeautifier : public XMLParserClient {
public:
    XMLBeautifier(bool indention, bool coloring);
    virtual ~XMLBeautifier();

    std::string beautify(const std::string&);

private:
    void handleStartElement(const std::string& element, const std::string& ns, const AttributeMap& attributes);
    void handleEndElement(const std::string& element, const std::string& ns);
    void handleCharacterData(const std::string& data);

private:
    void indent();

private:
    std::string styleTag(const std::string& text) const;
    std::string styleNamespace(const std::string& text) const;
    std::string styleAttribute(const std::string& text) const;
    std::string styleValue(const std::string& text) const;

private:
    bool doIndention;
    bool doColoring;

    int intLevel;
    std::string inputBuffer;
    std::stringstream buffer;
    XMLParserFactory* factory;
    XMLParser* parser;

    bool lastWasStepDown;
    std::stack<std::string> parentNSs;
};
}
