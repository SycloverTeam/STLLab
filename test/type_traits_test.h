#ifndef __TEST_TYPE_TRAITS_TEST__
#define __TEST_TYPE_TRAITS_TEST__

#include "cppunit/cppunit_mini.h"
namespace test {

class type_trait_test : public __test_base {
public:
  CPPUNIT_TEST_START(type_trait_test)
  CPPUNIT_TEST_BODY(integer)
  CPPUNIT_TEST_BODY(trivial_destructor)
  CPPUNIT_TEST_BODY(is_POD)
  CPPUNIT_TEST_END()
private:
  void integer();
  void trivial_destructor();
  void is_POD();
};

} // namespace test
#endif // __TEST_TYPE_TRAITS_TEST__