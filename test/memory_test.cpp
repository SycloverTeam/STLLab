#include "memory_test.h"
#include "memory"
using tinystl::auto_ptr;

auto_ptr<int> create_auto_ptr(int __value) {
  return auto_ptr<int>(new int(__value));
}

bool check_equality(auto_ptr<int> __a, int __v) { return *__a == __v; }

void test::memory_test::auto_ptr_test() {
  {
    auto_ptr<int> pint(new int(1));
    CPPUNIT_ASSERT(*pint == 1);
    *pint = 2;
    CPPUNIT_ASSERT(*pint == 2);
  }

  {
    auto_ptr<int> pint(create_auto_ptr(3));
    CPPUNIT_ASSERT(*pint == 3);
    CPPUNIT_ASSERT(check_equality(pint, 3));
  }

  {
    auto_ptr<const int> pint(new int(2));
    CPPUNIT_ASSERT(*pint == 2);
  }
  {
    auto_ptr<volatile int> pint(new int(2));
    CPPUNIT_ASSERT(*pint == 2);
  }
  {
    auto_ptr<const volatile int> pint(new int(2));
    CPPUNIT_ASSERT(*pint == 2);
  }
}