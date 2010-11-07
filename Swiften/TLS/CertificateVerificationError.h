/*
 * Copyright (c) 2010 Remko Tronçon
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#pragma once

namespace Swift {
	class CertificateVerificationError {
		public:
			enum Type {
				UnknownError,
				Expired,
				NotYetValid,
				SelfSigned,
				Rejected,
				Untrusted,
				InvalidPurpose,
				PathLengthExceeded,
				InvalidSignature,
				InvalidCA,
			};

			CertificateVerificationError(Type type = UnknownError) : type(type) {}

			Type getType() const { 
				return type; 
			}

		private:
			Type type;
	};
}
