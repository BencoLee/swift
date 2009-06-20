#include "Swiften/Avatars/AvatarFileStorage.h"

#include <iostream>
#include <boost/filesystem/fstream.hpp>

namespace Swift {

AvatarFileStorage::AvatarFileStorage(const boost::filesystem::path& path) : path_(path) {
	boost::filesystem::create_directory(path_);
}

bool AvatarFileStorage::hasAvatar(const String& hash) const { 
	return boost::filesystem::exists(getAvatarPath(hash));
}

void AvatarFileStorage::addAvatar(const String& hash, const ByteArray& avatar) {
	boost::filesystem::ofstream file(getAvatarPath(hash), boost::filesystem::ofstream::binary|boost::filesystem::ofstream::out);
	file.write(avatar.getData(), avatar.getSize());
	file.close();
}

boost::filesystem::path AvatarFileStorage::getAvatarPath(const String& hash) const {
	return path_ / hash.getUTF8String();
}

}
