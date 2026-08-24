#include "stdafx.h"
#include "CppUnitTest.h"

#include <map>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unittest_map
{
    typedef std::pair <std::string, std::string> StringPair;
    typedef std::map <std::string, std::string> StringMap;

    TEST_CLASS(TestMapIO)
    {
    public:

        TEST_METHOD(TestAddByBracket) {
            StringMap m;
            m["first entry"] = "this is data for 'first entry'";
            Assert::AreEqual(m["first entry"], std::string("this is data for 'first entry'"));
        }

        TEST_METHOD(TestAddByInsert) {
            StringMap m;
            StringPair p("first entry", "this is data for 'first entry'");
            m.insert(p);
            Assert::AreEqual(m["first entry"], std::string("this is data for 'first entry'"));
        }

        TEST_METHOD(TestGetMissingKeyIsEmpty) {
            StringMap m;
            std::string b = m[std::string("this key does not exist")];
            Assert::IsTrue(b.empty());
        }

        TEST_METHOD(TestGetMissingKeyIsEmptyByIterator) {
            StringMap m;
            StringMap::iterator stringMapIterator = m.find("missing key");
            Assert::IsTrue(stringMapIterator == m.end());
        }
    };
}