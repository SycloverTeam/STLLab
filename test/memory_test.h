#ifndef __TEST_MEMORY_TEST__
#define __TEST_MEMORY_TEST__
#include "cppunit/cppunit_mini.h"

namespace test {
class memory_test : public __test_base {
  CPPUNIT_TEST_START(memory_test)
  CPPUNIT_TEST_BODY(auto_ptr_test)
  CPPUNIT_TEST_END()

private:
  void auto_ptr_test();
};

} // namespace test

#endif // __TEST_MEMORY_TEST__