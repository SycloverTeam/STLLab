#ifndef __TEST_ALLOCATOR_TEST__
#define __TEST_ALLOCATOR_TEST__

#include "cppunit/cppunit_mini.h"
#include "stl_alloc.h"
namespace test {
class allocator_test : public __test_base {
  CPPUNIT_TEST_START(allocator_test)
  CPPUNIT_TEST_BODY(zero_allocation)
  CPPUNIT_TEST_BODY(bad_alloc_test)
  CPPUNIT_TEST_END()

private:
  void zero_allocation();
  void bad_alloc_test();
};
} // namespace test

#endif //__TEST_ALLOCATOR_TEST__