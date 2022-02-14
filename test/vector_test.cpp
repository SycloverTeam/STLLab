#include "vector_test.h"
#include "cppunit/cppunit_mini.h"

#include "stl_vector.h"
#include "type_traits.h"
using tinystl::__type_traits;
using tinystl::allocator;
using tinystl::vector;

struct TestStruct {
  unsigned int a[3];
};

template <class _Tp> struct NotSTLportAllocator : public allocator<_Tp> {
  template <class _Tp1> struct rebind {
    typedef NotSTLportAllocator<_Tp1> other;
  };
  NotSTLportAllocator() {}
  template <class _Tp1>
  NotSTLportAllocator(const NotSTLportAllocator<_Tp1> &) {}
  NotSTLportAllocator(const NotSTLportAllocator<_Tp> &) {}
  ~NotSTLportAllocator() {}
};

struct Point {
  int x, y;
};

struct PointEx : public Point {
  PointEx() : builtFromBase(false) {}
  PointEx(const Point &) : builtFromBase(true) {}

  bool builtFromBase;
};

template <> struct __type_traits<PointEx> {
  typedef __false_type has_trivial_default_constructor;
  typedef __true_type has_trivial_copy_constructor;
  typedef __true_type has_trivial_assignment_operator;
  typedef __true_type has_trivial_destructor;
  typedef __true_type is_POD_type;
};

void test::vector_test::vector_test_1() {
  vector<int> v1;
  CPPUNIT_ASSERT(v1.empty() == true)
  v1.push_back(42);
  CPPUNIT_ASSERT(v1.size() == 1)
  CPPUNIT_ASSERT(v1[0] == 42)

  {
    vector<vector<int>> vec(10);
    vector<vector<int>>::iterator it(vec.begin()), end(vec.end());
    for (; it != end; ++it) {
      CPPUNIT_ASSERT((*it).empty());
      CPPUNIT_ASSERT((*it).size() == 0);
      CPPUNIT_ASSERT((*it).capacity() == 0);
      CPPUNIT_ASSERT((*it).begin() == (*it).end());
    }
  }
}

void test::vector_test::vector_test_2() {
  vector<double> v1; // Empty vector of doubles.
  v1.push_back(32.1);
  v1.push_back(40.5);
  vector<double> v2; // Another empty vector of doubles.
  v2.push_back(3.56);

  CPPUNIT_ASSERT(v1.size() == 2);
  CPPUNIT_ASSERT(v1[0] == 32.1);
  CPPUNIT_ASSERT(v1[1] == 40.5);

  CPPUNIT_ASSERT(v2.size() == 1);
  CPPUNIT_ASSERT(v2[0] == 3.56);
  size_t v1Cap = v1.capacity();
  size_t v2Cap = v2.capacity();

  v1.swap(v2); // Swap the vector's contents.

  CPPUNIT_ASSERT(v1.size() == 1);
  CPPUNIT_ASSERT(v1.capacity() == v2Cap);
  CPPUNIT_ASSERT(v1[0] == 3.56);

  CPPUNIT_ASSERT(v2.size() == 2);
  CPPUNIT_ASSERT(v2.capacity() == v1Cap);
  CPPUNIT_ASSERT(v2[0] == 32.1);
  CPPUNIT_ASSERT(v2[1] == 40.5);

  v2 = v1; // Assign one vector to another.

  CPPUNIT_ASSERT(v2.size() == 1);
  CPPUNIT_ASSERT(v2[0] == 3.56);
}

void test::vector_test::vector_test_3() {
  typedef vector<char> vec_type;

  vec_type v1; // Empty vector of characters.
  v1.push_back('h');
  v1.push_back('i');

  CPPUNIT_ASSERT(v1.size() == 2);
  CPPUNIT_ASSERT(v1[0] == 'h');
  CPPUNIT_ASSERT(v1[1] == 'i');

  vec_type v2(v1.begin(), v1.end());
  v2[1] = 'o'; // Replace second character.

  CPPUNIT_ASSERT(v2.size() == 2);
  CPPUNIT_ASSERT(v2[0] == 'h');
  CPPUNIT_ASSERT(v2[1] == 'o');

  CPPUNIT_ASSERT((v1 == v2) == false);

  CPPUNIT_ASSERT((v1 < v2) == true);
}

void test::vector_test::vector_test_4() {
  vector<int> v(4);

  v[0] = 1;
  v[1] = 4;
  v[2] = 9;
  v[3] = 16;

  CPPUNIT_ASSERT(v.front() == 1);
  CPPUNIT_ASSERT(v.back() == 16);

  v.push_back(25);

  CPPUNIT_ASSERT(v.back() == 25);
  CPPUNIT_ASSERT(v.size() == 5);

  v.pop_back();

  CPPUNIT_ASSERT(v.back() == 16);
  CPPUNIT_ASSERT(v.size() == 4);
}
void test::vector_test::vector_test_5() {
  int array[] = {1, 4, 9, 16};

  vector<int> v(array, array + 4);

  CPPUNIT_ASSERT(v.size() == 4);

  CPPUNIT_ASSERT(v[0] == 1);
  CPPUNIT_ASSERT(v[1] == 4);
  CPPUNIT_ASSERT(v[2] == 9);
  CPPUNIT_ASSERT(v[3] == 16);
}

void test::vector_test::vector_test_6() {
  int array[] = {1, 4, 9, 16, 25, 36};

  vector<int> v(array, array + 6);
  vector<int>::iterator vit;

  CPPUNIT_ASSERT(v.size() == 6);
  CPPUNIT_ASSERT(v[0] == 1);
  CPPUNIT_ASSERT(v[1] == 4);
  CPPUNIT_ASSERT(v[2] == 9);
  CPPUNIT_ASSERT(v[3] == 16);
  CPPUNIT_ASSERT(v[4] == 25);
  CPPUNIT_ASSERT(v[5] == 36);

  vit = v.erase(v.begin()); // Erase first element.
  CPPUNIT_ASSERT(*vit == 4);

  CPPUNIT_ASSERT(v.size() == 5);
  CPPUNIT_ASSERT(v[0] == 4);
  CPPUNIT_ASSERT(v[1] == 9);
  CPPUNIT_ASSERT(v[2] == 16);
  CPPUNIT_ASSERT(v[3] == 25);
  CPPUNIT_ASSERT(v[4] == 36);

  vit = v.erase(v.end() - 1); // Erase last element.
  CPPUNIT_ASSERT(vit == v.end());

  CPPUNIT_ASSERT(v.size() == 4);
  CPPUNIT_ASSERT(v[0] == 4);
  CPPUNIT_ASSERT(v[1] == 9);
  CPPUNIT_ASSERT(v[2] == 16);
  CPPUNIT_ASSERT(v[3] == 25);

  v.erase(v.begin() + 1, v.end() - 1); // Erase all but first and last.

  CPPUNIT_ASSERT(v.size() == 2);
  CPPUNIT_ASSERT(v[0] == 4);
  CPPUNIT_ASSERT(v[1] == 25);
}

void test::vector_test::vector_test_7() {
  int array1[] = {1, 4, 25};
  int array2[] = {9, 16};

  vector<int> v(array1, array1 + 3);
  vector<int>::iterator vit;
  vit = v.insert(v.begin(), 0); // Insert before first element.
  CPPUNIT_ASSERT(*vit == 0);

  vit = v.insert(v.end(), 36); // Insert after last element.
  CPPUNIT_ASSERT(*vit == 36);

  CPPUNIT_ASSERT(v.size() == 5);
  CPPUNIT_ASSERT(v[0] == 0);
  CPPUNIT_ASSERT(v[1] == 1);
  CPPUNIT_ASSERT(v[2] == 4);
  CPPUNIT_ASSERT(v[3] == 25);
  CPPUNIT_ASSERT(v[4] == 36);

  // Insert contents of array2 before fourth element.
  v.insert(v.begin() + 3, array2, array2 + 2);

  CPPUNIT_ASSERT(v.size() == 7);

  CPPUNIT_ASSERT(v[0] == 0);
  CPPUNIT_ASSERT(v[1] == 1);
  CPPUNIT_ASSERT(v[2] == 4);
  CPPUNIT_ASSERT(v[3] == 9);
  CPPUNIT_ASSERT(v[4] == 16);
  CPPUNIT_ASSERT(v[5] == 25);
  CPPUNIT_ASSERT(v[6] == 36);

  v.clear();
  CPPUNIT_ASSERT(v.empty());

  v.insert(v.begin(), 5, 10);
  CPPUNIT_ASSERT(v.size() == 5);
  CPPUNIT_ASSERT(v[0] == 10);
  CPPUNIT_ASSERT(v[1] == 10);
  CPPUNIT_ASSERT(v[2] == 10);
  CPPUNIT_ASSERT(v[3] == 10);
  CPPUNIT_ASSERT(v[4] == 10);

  /*
  {
    vector<float> vf(2.0f, 3.0f);
    CPPUNIT_ASSERT( vf.size() == 2 );
    CPPUNIT_ASSERT( vf.front() == 3.0f );
    CPPUNIT_ASSERT( vf.back() == 3.0f );
  }
  */
}

void test::vector_test::capacity() {
  {
    vector<int> v;

    CPPUNIT_ASSERT(v.capacity() == 0);
    v.push_back(42);
    CPPUNIT_ASSERT(v.capacity() >= 1);
    v.reserve(5000);
    CPPUNIT_ASSERT(v.capacity() >= 5000);
  }

  {
    // Test that used to generate an assertion when using __debug_alloc.
    vector<TestStruct> va;
    va.reserve(1);
    va.reserve(2);
  }
}

void test::vector_test::at() {
  vector<int> v;
  vector<int> const &cv = v;

  v.push_back(10);
  CPPUNIT_ASSERT(v.at(0) == 10);
  v.at(0) = 20;
  CPPUNIT_ASSERT(cv.at(0) == 20);

  // try {
  //   v.at(1) = 20;
  //   CPPUNIT_FAIL;
  // } catch (out_of_range const &) {
  // } catch (...) {
  //   CPPUNIT_FAIL;
  // }
}

void test::vector_test::pointer() {
  vector<int *> v1;
  vector<int *> v2 = v1;
  vector<int *> v3;

  v3.insert(v3.end(), v1.begin(), v1.end());
}

void test::vector_test::auto_ref() {
  vector<int> ref;
  for (int i = 0; i < 5; ++i) {
    ref.push_back(i);
  }

  vector<vector<int>> v_v_int(1, ref);
  v_v_int.push_back(v_v_int[0]);
  v_v_int.push_back(ref);
  v_v_int.push_back(v_v_int[0]);
  v_v_int.push_back(v_v_int[0]);
  v_v_int.push_back(ref);

  vector<vector<int>>::iterator vvit(v_v_int.begin()), vvitEnd(v_v_int.end());
  for (; vvit != vvitEnd; ++vvit) {
    CPPUNIT_ASSERT(*vvit == ref);
  }
}

// void test::vector_test::allocator_with_state() {
//   char buf1[1024];
//   StackAllocator<int>
//   stack1(buf1, buf1 + sizeof(buf1));

//   char buf2[1024];
//   StackAllocator<int> stack2(buf2, buf2 + sizeof(buf2));

//   {
//     typedef vector<int, StackAllocator<int>> VectorInt;
//     VectorInt vint1(10, 0, stack1);
//     VectorInt vint1Cpy(vint1);

//     VectorInt vint2(10, 1, stack2);
//     VectorInt vint2Cpy(vint2);

//     vint1.swap(vint2);

//     CPPUNIT_ASSERT(vint1.get_allocator().swaped());
//     CPPUNIT_ASSERT(vint2.get_allocator().swaped());

//     CPPUNIT_ASSERT(vint1 == vint2Cpy);
//     CPPUNIT_ASSERT(vint2 == vint1Cpy);
//     CPPUNIT_ASSERT(vint1.get_allocator() == stack2);
//     CPPUNIT_ASSERT(vint2.get_allocator() == stack1);
//   }
//   CPPUNIT_ASSERT(stack1.ok());
//   CPPUNIT_ASSERT(stack2.ok());
// }

void test::vector_test::optimizations_check() {
  vector<Point> v1(1);
  CPPUNIT_ASSERT(v1.size() == 1);

  vector<PointEx> v2(v1.begin(), v1.end());
  CPPUNIT_ASSERT(v2.size() == 1);
  CPPUNIT_ASSERT(v2[0].builtFromBase == true);
}

void test::vector_test::assign_check() {
  vector<int> v(3, 1);
  int array[] = {1, 2, 3, 4, 5};

  v.assign(array, array + 5);
  CPPUNIT_CHECK(v[4] == 5);
  CPPUNIT_CHECK(v[0] == 1);
  CPPUNIT_CHECK(v[1] == 2);
}

void test::vector_test::iterators() {
  vector<int> vint(10, 0);
  vector<int> const &crvint = vint;

  CPPUNIT_ASSERT(vint.begin() == vint.begin());
  CPPUNIT_ASSERT(crvint.begin() == vint.begin());
  CPPUNIT_ASSERT(vint.begin() == crvint.begin());
  CPPUNIT_ASSERT(crvint.begin() == crvint.begin());

  CPPUNIT_ASSERT(vint.begin() != vint.end());
  CPPUNIT_ASSERT(crvint.begin() != vint.end());
  CPPUNIT_ASSERT(vint.begin() != crvint.end());
  CPPUNIT_ASSERT(crvint.begin() != crvint.end());

  CPPUNIT_ASSERT(vint.rbegin() == vint.rbegin());

  CPPUNIT_ASSERT(crvint.rbegin() == crvint.rbegin());

  CPPUNIT_ASSERT(vint.rbegin() != vint.rend());

  CPPUNIT_ASSERT(crvint.rbegin() != crvint.rend());
}

void test::vector_test::ebo() {
  typedef vector<int, NotSTLportAllocator<int>> V;
  V *pv1 = new V(1, 1);
  V *pv2 = new V(10, 2);

  size_t v1Capacity = pv1->capacity();
  size_t v2Capacity = pv2->capacity();

  pv1->swap(*pv2);

  CPPUNIT_ASSERT(pv1->size() == 10);
  CPPUNIT_ASSERT(pv1->capacity() == v2Capacity);
  CPPUNIT_ASSERT((*pv1)[5] == 2);

  CPPUNIT_ASSERT(pv2->size() == 1);
  CPPUNIT_ASSERT(pv2->capacity() == v1Capacity);
  CPPUNIT_ASSERT((*pv2)[0] == 1);

  delete pv2;
  delete pv1;
}
