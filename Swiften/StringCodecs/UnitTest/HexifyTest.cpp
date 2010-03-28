#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

#include "Swiften/StringCodecs/Hexify.h"
#include "Swiften/Base/String.h"
#include "Swiften/Base/ByteArray.h"

using namespace Swift;

class HexifyTest : public CppUnit::TestFixture {
		CPPUNIT_TEST_SUITE(HexifyTest);
		CPPUNIT_TEST(testHexify);
		CPPUNIT_TEST_SUITE_END();

	public:
		void testHexify() {
			CPPUNIT_ASSERT_EQUAL(String("4206b23ca6b0a643d20d89b04ff58cf78b8096ed"), Hexify::hexify(ByteArray("\x42\x06\xb2\x3c\xa6\xb0\xa6\x43\xd2\x0d\x89\xb0\x4f\xf5\x8c\xf7\x8b\x80\x96\xed")));
		}
};

CPPUNIT_TEST_SUITE_REGISTRATION(HexifyTest);
