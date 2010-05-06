/*
 * Copyright (c) 2010 Remko Tronçon
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

#include "Swiften/Parser/PayloadParsers/StorageParser.h"
#include "Swiften/Parser/PayloadParsers/UnitTest/PayloadsParserTester.h"

using namespace Swift;

class StorageParserTest : public CppUnit::TestFixture {
		CPPUNIT_TEST_SUITE(StorageParserTest);
		CPPUNIT_TEST(testParse_Conference);
		CPPUNIT_TEST(testParse_MultipleConferences);
		CPPUNIT_TEST(testParse_URL);
		CPPUNIT_TEST_SUITE_END();

	public:
		StorageParserTest() {}

		void testParse_Conference() {
			PayloadsParserTester parser;

			CPPUNIT_ASSERT(parser.parse(
				"<storage xmlns='storage:bookmarks'>"
					"<conference "
							"name='Council of Oberon' "
							"autojoin='true' jid='council@conference.underhill.org'>"
						"<nick>Puck</nick>"
						"<password>MyPass</password>"
					"</conference>"
				"</storage>"));

			Storage* payload = dynamic_cast<Storage*>(parser.getPayload().get());
			std::vector<Storage::Conference> conferences = payload->getConferences();
			CPPUNIT_ASSERT_EQUAL(1, static_cast<int>(conferences.size()));
			CPPUNIT_ASSERT_EQUAL(String("Council of Oberon"), conferences[0].name);
			CPPUNIT_ASSERT_EQUAL(JID("council@conference.underhill.org"), conferences[0].jid);
			CPPUNIT_ASSERT(conferences[0].autoJoin);
			CPPUNIT_ASSERT_EQUAL(String("Puck"), conferences[0].nick);
			CPPUNIT_ASSERT_EQUAL(String("MyPass"), conferences[0].password);
		}

		void testParse_MultipleConferences() {
			PayloadsParserTester parser;

			CPPUNIT_ASSERT(parser.parse(
				"<storage xmlns='storage:bookmarks'>"
					"<conference "
							"name='Council of Oberon' "
							"jid='council@conference.underhill.org' />"
					"<conference "
							"name='Tea party' "
							"jid='teaparty@wonderland.lit' />"
				"</storage>"));

			Storage* payload = dynamic_cast<Storage*>(parser.getPayload().get());
			std::vector<Storage::Conference> conferences = payload->getConferences();
			CPPUNIT_ASSERT_EQUAL(2, static_cast<int>(conferences.size()));
			CPPUNIT_ASSERT_EQUAL(String("Council of Oberon"), conferences[0].name);
			CPPUNIT_ASSERT_EQUAL(JID("council@conference.underhill.org"), conferences[0].jid);
			CPPUNIT_ASSERT_EQUAL(String("Tea party"), conferences[1].name);
			CPPUNIT_ASSERT_EQUAL(JID("teaparty@wonderland.lit"), conferences[1].jid);
		}

		void testParse_URL() {
			PayloadsParserTester parser;

			CPPUNIT_ASSERT(parser.parse(
				"<storage xmlns='storage:bookmarks'>"
					"<url name='Complete Works of Shakespeare' url='http://the-tech.mit.edu/Shakespeare/'/>"
				"</storage>"));

			Storage* payload = dynamic_cast<Storage*>(parser.getPayload().get());
			std::vector<Storage::URL> urls = payload->getURLs();
			CPPUNIT_ASSERT_EQUAL(1, static_cast<int>(urls.size()));
			CPPUNIT_ASSERT_EQUAL(String("Complete Works of Shakespeare"), urls[0].name);
			CPPUNIT_ASSERT_EQUAL(String("http://the-tech.mit.edu/Shakespeare/"), urls[0].url);
		}

};

CPPUNIT_TEST_SUITE_REGISTRATION(StorageParserTest);
