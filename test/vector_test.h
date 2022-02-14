#ifndef __TEST_VECTOR_TEST__
#define __TEST_VECTOR_TEST__

#include "cppunit/cppunit_mini.h"
namespace test {

class vector_test : public __test_base {
  CPPUNIT_TEST_START(vector_test)
  CPPUNIT_TEST_BODY(vector_test_1)
  CPPUNIT_TEST_BODY(vector_test_2)
  CPPUNIT_TEST_BODY(vector_test_3)
  CPPUNIT_TEST_BODY(vector_test_4)
  CPPUNIT_TEST_BODY(vector_test_5)
  CPPUNIT_TEST_BODY(vector_test_6)
  CPPUNIT_TEST_BODY(vector_test_7)
  CPPUNIT_TEST_BODY(capacity)
  CPPUNIT_TEST_BODY(at)
  CPPUNIT_TEST_BODY(pointer);
  CPPUNIT_TEST_BODY(auto_ref);
  // CPPUNIT_TEST_BODY(allocator_with_state);
  CPPUNIT_TEST_BODY(iterators);
  CPPUNIT_TEST_BODY(optimizations_check);
  CPPUNIT_TEST_BODY(assign_check);
  CPPUNIT_TEST_BODY(ebo);
  CPPUNIT_TEST_END()

private:
  void vector_test_1();
  void vector_test_2();
  void vector_test_3();
  void vector_test_4();
  void vector_test_5();
  void vector_test_6();
  void vector_test_7();
  void capacity();
  void at();
  void pointer();
  void auto_ref();
  // void allocator_with_state();
  void iterators();
  void optimizations_check();
  void assign_check();
  void ebo();
};

} // namespace test

#endif // __TEST_VECTOR_TEST__