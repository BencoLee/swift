#ifndef SWIFTEN_STANZAS_VERSION_H
#define SWIFTEN_STANZAS_VERSION_H

#include "Swiften/Base/String.h"
#include "Swiften/Elements/Payload.h"

namespace Swift {
	class Version : public Payload
	{
		public:
			Version(const String& name = "", const String& version = "", const String& os = "") : name_(name), version_(version), os_(os) { }

			const String& getName() const { return name_; }
			const String& getVersion() const { return version_; }
			const String& getOS() const { return os_; }

		private:
			String name_;
			String version_;
			String os_;
	};
}

#endif
