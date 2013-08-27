/*
 * Copyright (c) 2010 Remko Tronçon
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#include <Swiften/Client/ClientXMLTracer.h>

#include <iostream>
#include <boost/bind.hpp>

#include <Swiften/Base/Platform.h>

namespace Swift {

ClientXMLTracer::ClientXMLTracer(CoreClient* client, bool bosh) : bosh(bosh) {
#ifdef SWIFTEN_PLATFORM_WIN32
	beautifier = new XMLBeautifier(true, false);
#else
	beautifier = new XMLBeautifier(true, true);
#endif
	client->onDataRead.connect(boost::bind(&ClientXMLTracer::printData, this, '<', _1));
	client->onDataWritten.connect(boost::bind(&ClientXMLTracer::printData, this, '>', _1));
}

ClientXMLTracer::~ClientXMLTracer() {
	delete beautifier;
}

void ClientXMLTracer::printData(char direction, const SafeByteArray& data) {
	printLine(direction);
	if (bosh) {
		std::string line = byteArrayToString(ByteArray(data.begin(), data.end())); 
// Disabled because it swallows bits of XML (namespaces, if I recall)
//		size_t endOfHTTP = line.find("\r\n\r\n");
//		if (false && endOfHTTP != std::string::npos) {
//			std::cerr << line.substr(0, endOfHTTP) << std::endl << beautifier->beautify(line.substr(endOfHTTP)) << std::endl;
//		}
//		else {
			std::cerr << line << std::endl;
//		}
	}
	else {
		std::cerr << beautifier->beautify(byteArrayToString(ByteArray(data.begin(), data.end()))) << std::endl;
	}
}

void ClientXMLTracer::printLine(char c) {
	for (unsigned int i = 0; i < 80; ++i) {
		std::cerr << c;
	}
	std::cerr << std::endl;
}

}
