#include "type_traits_test.h"
#include "type_traits.h"

using tinystl::__false_type;
using tinystl::__true_type;
using tinystl::__type_traits;
using tinystl::_Is_integer;

int type_to_value(__true_type) { return 1; }
int type_to_value(__false_type) { return 0; }

template <typename _Type> int is_integer(_Type) {
  typedef typename _Is_integer<_Type>::_Integral _Integral;
  return type_to_value(_Integral());
}

template <typename _Tp> int has_trivial_destructor(_Tp) {
  typedef
      typename __type_traits<_Tp>::has_trivial_destructor _TrivialDestructor;
  return type_to_value(_TrivialDestructor());
}

template <typename _Tp> int is_POD_type(_Tp) {
  typedef typename __type_traits<_Tp>::is_POD_type _IsPODType;
  return type_to_value(_IsPODType());
}

int *int_pointer;
int const *int_const_pointer;
int volatile *int_volatile_pointer;
int const volatile *int_const_volatile_pointer;
int int_val = 0;
int const int_const_val = 0;
int volatile int_volatile_val = 0;
int &int_ref = int_val;
int const &int_const_ref = int_val;
int const volatile &int_const_volatile_ref = int_val;

// A type that represent any type:
struct any_type {
  // Dummy operations to forbid to compilers with intrinsic
  // type traits support to consider this type as a POD.
  any_type() : m_data(1) {}
  any_type(const any_type &) : m_data(2) {}
  any_type &operator=(const any_type &) {
    m_data = 3;
    return *this;
  }
  ~any_type() { m_data = 0; }

  size_t m_data;
};

any_type any;
any_type *any_pointer;
any_type const *any_const_pointer;
any_type volatile *any_volatile_pointer;
any_type const volatile *any_const_volatile_pointer;

// A type that represent any pod type
struct any_pod_type {};

any_pod_type any_pod;
any_pod_type *any_pod_pointer;
any_pod_type const *any_pod_const_pointer;
any_pod_type volatile *any_pod_volatile_pointer;
any_pod_type const volatile *any_pod_const_volatile_pointer;

void test::type_trait_test::integer() {

  CPPUNIT_ASSERT(is_integer(bool()) == 1);
  CPPUNIT_ASSERT(is_integer(char()) == 1);
  typedef signed char signed_char;
  CPPUNIT_ASSERT(is_integer(signed_char()) == 1);
  typedef unsigned char unsigned_char;
  CPPUNIT_ASSERT(is_integer(unsigned_char()) == 1);
  CPPUNIT_ASSERT(is_integer(short()) == 1);
  typedef unsigned short unsigned_short;
  CPPUNIT_ASSERT(is_integer(unsigned_short()) == 1);
  CPPUNIT_ASSERT(is_integer(int()) == 1);
  typedef unsigned int unsigned_int;
  CPPUNIT_ASSERT(is_integer(unsigned_int()) == 1);
  CPPUNIT_ASSERT(is_integer(long()) == 1);
  typedef unsigned long unsigned_long;
  CPPUNIT_ASSERT(is_integer(unsigned_long()) == 1);
  CPPUNIT_ASSERT(is_integer(float()) == 0);
  CPPUNIT_ASSERT(is_integer(double()) == 0);
  typedef long double long_double;
  CPPUNIT_ASSERT(is_integer(long_double()) == 0);
  CPPUNIT_ASSERT(is_integer(any) == 0);
  CPPUNIT_ASSERT(is_integer(any_pointer) == 0);
}

void test::type_trait_test::trivial_destructor() {
  CPPUNIT_CHECK(has_trivial_destructor(int_pointer) == 1);
  CPPUNIT_CHECK(has_trivial_destructor(int_const_pointer) == 1);
  CPPUNIT_CHECK(has_trivial_destructor(int_volatile_pointer) == 1);
  CPPUNIT_CHECK(has_trivial_destructor(int_const_volatile_pointer) == 1);
  CPPUNIT_CHECK(has_trivial_destructor(any_pointer) == 1);
  CPPUNIT_CHECK(has_trivial_destructor(any) == 0);
  CPPUNIT_CHECK(has_trivial_destructor(any_pointer) == 1);

  /*
    !todo:
        this position need to determine the `POD`.
        not implemented in sgistl.
        and the implementation in stlport has not been understood.

  */
  //   CPPUNIT_CHECK(has_trivial_destructor(any_pod) == 1);

  // The implementation of string is needed here.
  //   CPPUNIT_CHECK(has_trivial_destructor(string()) == 0);

  // The implementation of vector is needed here.
  // Check of the meta information impact in a container implementation
  //   {
  //     vector<DestructorMonitor> v(10);
  //     DestructorMonitor::nb_destructor_call = 0;
  //   }
  //   CPPUNIT_CHECK(DestructorMonitor::nb_destructor_call == 0);
}

void test::type_trait_test::is_POD() {
  CPPUNIT_CHECK(is_POD_type(int_pointer) == 1);
  CPPUNIT_CHECK(is_POD_type(int_const_pointer) == 1);
  CPPUNIT_CHECK(is_POD_type(int_volatile_pointer) == 1);
  CPPUNIT_CHECK(is_POD_type(int_const_volatile_pointer) == 1);
  CPPUNIT_CHECK(is_POD_type(any_pointer) == 1);
  CPPUNIT_CHECK(is_POD_type(any) == 0);
  CPPUNIT_CHECK(is_POD_type(any_pointer) == 1);

  //   CPPUNIT_CHECK(is_POD_type(any_pod) == 1);
  //   CPPUNIT_CHECK(is_POD_type(string()) == 0);
}
