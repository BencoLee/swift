/*
 * Copyright (c) 2010 Remko Tronçon
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#ifndef SWIFTEN_ZLibDecompressor_H
#define SWIFTEN_ZLibDecompressor_H

#include <cassert>

#include "Swiften/Compress/ZLibCodecompressor.h"
#include "Swiften/Base/ByteArray.h"

namespace Swift {
	class ZLibDecompressor : public ZLibCodecompressor {
		public:
			ZLibDecompressor() {
				int result = inflateInit(&stream_);
				assert(result == Z_OK);
				(void) result;
			}

			~ZLibDecompressor() {
				inflateEnd(&stream_);
			}

			virtual int processZStream() {
				return inflate(&stream_, Z_SYNC_FLUSH);
			}
	};
}

#endif
