/*
 * Copyright (c) 2013 Remko Tronçon
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

#include <Swiften/Parser/EnumParser.h>

using namespace Swift;

class EnumParserTest : public CppUnit::TestFixture {
		CPPUNIT_TEST_SUITE(EnumParserTest);
		CPPUNIT_TEST(testParse);
		CPPUNIT_TEST(testParse_NoValue);
		CPPUNIT_TEST_SUITE_END();

	public:
		enum MyEnum {
			MyValue1,
			MyValue2,
			MyValue3
		};

		void testParse() {
			CPPUNIT_ASSERT(MyValue2 == EnumParser<MyEnum>()(MyValue1, "my-value-1")(MyValue2, "my-value-2")(MyValue3, "my-value-3").parse("my-value-2"));
		}

		void testParse_NoValue() {
			CPPUNIT_ASSERT(!EnumParser<MyEnum>()(MyValue1, "my-value-1")(MyValue2, "my-value-2")(MyValue3, "my-value-3").parse("my-value-4"));
		}
};

CPPUNIT_TEST_SUITE_REGISTRATION(EnumParserTest);
