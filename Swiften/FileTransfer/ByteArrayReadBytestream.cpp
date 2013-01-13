/*
 * Copyright (c) 2010-2013 Remko Tronçon
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#include <Swiften/FileTransfer/ByteArrayReadBytestream.h>

#include <boost/smart_ptr/make_shared.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <Swiften/Base/Algorithm.h>

using namespace Swift;

boost::shared_ptr<ByteArray> ByteArrayReadBytestream::read(size_t size) {
	size_t readSize = size;
	if (position + readSize > data.size()) {
		readSize = data.size() - position;
	}
	boost::shared_ptr<ByteArray> result = boost::make_shared<ByteArray>(
			data.begin() + boost::numeric_cast<long long>(position), 
			data.begin() + boost::numeric_cast<long long>(position) + boost::numeric_cast<long long>(readSize));

	onRead(*result);
	position += readSize;
	return result;
}

void ByteArrayReadBytestream::addData(const std::vector<unsigned char>& moreData) {
	append(data, moreData);
	onDataAvailable();
}
