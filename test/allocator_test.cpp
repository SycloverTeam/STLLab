#include "allocator_test.h"

using test::allocator_test;

void allocator_test::zero_allocation() {
  typedef tinystl::allocator<char> char_allocator_t;
  char_allocator_t char_allocator;
  char *buf = char_allocator.allocate(0);
  char_allocator.deallocate(buf, 0);
  char_allocator.deallocate(0, 0);
}

struct big_struct {
  char _data[0x1000];
};

void allocator_test::bad_alloc_test() {
  typedef tinystl::allocator<big_struct> big_struct_allocator_t;
  big_struct_allocator_t big_struct_allocator;

  try {
    big_struct_allocator_t::pointer p_big_struct =
        big_struct_allocator.allocate(0x100 * 0x100 * 0x100);

    CPPUNIT_ASSERT(p_big_struct != 0);
  } catch (bad_alloc const &) {
  } catch (...) {
    CPPUNIT_FAIL
  }
}
