#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#include "all_gene_topo.hpp"

#pragma GCC diagnostic ignored "-Wwrite-strings"

class TestGeneTopoList : public CppUnit::TestCase {

  CPPUNIT_TEST_SUITE( TestGeneTopoList );
  CPPUNIT_TEST ( testConstructor );
  CPPUNIT_TEST ( testExtract );
  CPPUNIT_TEST_SUITE_END();
 private:

 public:
  void setUp() {
        return;
    }

    void tearDown() {
        return;
    }

    void testConstructor(){
        const char *vinit3[] = {"a", "b", "c"};
        std::vector<std::string> v3(vinit3, end(vinit3));
        GeneTopoList testList3(v3);
        CPPUNIT_ASSERT (  testList3.TipLabels.size() == (unsigned)3 );
        CPPUNIT_ASSERT (  testList3.TreeList.size() == (unsigned)3 );

        const char *vinit4[] = {"a", "b", "c", "d"};
        std::vector<std::string> v4(vinit4, end(vinit4));
        GeneTopoList testList4(v4);
        CPPUNIT_ASSERT (  testList4.TipLabels.size() == (unsigned)4 );
        CPPUNIT_ASSERT (  testList4.TreeList.size() == (unsigned)15 );

        const char *vinit5[] = {"a", "b", "c", "d", "e"};
        std::vector<std::string> v5(vinit5, end(vinit5));
        GeneTopoList testList5(v5);
        CPPUNIT_ASSERT (  testList5.TipLabels.size() == (unsigned)5 );
        CPPUNIT_ASSERT (  testList5.TreeList.size() == (unsigned)105 );

        const char *vinit6[] = {"a", "b", "c", "1", "2", "3"};
        std::vector<std::string> v6(vinit6, end(vinit6));
        GeneTopoList testList6(v6);
        CPPUNIT_ASSERT (  testList6.TipLabels.size() == (unsigned)6 );
        CPPUNIT_ASSERT (  testList6.TreeList.size() == (unsigned)945 );

    }

    void testExtract(){
        GeneTopoList testList;
        string tree = "(((A,B),C),D);";
        CPPUNIT_ASSERT_NO_THROW(testList.extract_TipLabels_from_TreeStr(tree));
        CPPUNIT_ASSERT (  testList.TipLabels.size() == (unsigned)4 );
        CPPUNIT_ASSERT_NO_THROW(testList.init());
        CPPUNIT_ASSERT_NO_THROW(testList.core());
        CPPUNIT_ASSERT (  testList.TreeList.size() == (unsigned)15 );
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( TestGeneTopoList );
