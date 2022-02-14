
#ifndef __CPPUNIT_CPPUNIT_MINI__
#define __CPPUNIT_CPPUNIT_MINI__

#include <cstdio>
#include <i386/types.h>
namespace test {

class __reporter_base {
public:
  virtual ~__reporter_base() {}
  virtual void error(const char * /*macroName*/, const char * /*in_macro*/,
                     const char * /*in_file*/, int /*in_line*/) {}
  virtual void message(const char * /* msg */) {}
  virtual void progress(const char * /*in_className*/,
                        const char * /*in_testName*/) {}
  virtual void printSummary() {}
};

class __test_base {
public:
  __test_base() { register_test(this); };

  virtual void __run() = 0;

  static inline void register_test(__test_base *__test);

  static void progress(const char *__class_name, const char *__function_name) {
    reporter->progress(__class_name, __function_name);
  }

  static void error(const char *__msg, const char *__function_name,
                    const char *__in_file, int __in_line) {
    reporter->error(__msg, __function_name, __in_file, __in_line);
  }
  static void message(const char *__msg) { reporter->message(__msg); }

  static void set_reporter(__reporter_base *__re) { reporter = __re; }

private:
  static __reporter_base *reporter;

public:
  __test_base *next;
};

} // namespace test

static test::__test_base *test_root = 0;

inline void test::__test_base::register_test(test::__test_base *__test) {
  __test->next = test_root;
  test_root = __test;
}

// macro to set test case

#define CPPUNIT_TEST_START(X)                                                  \
  typedef test::__test_base base;                                              \
  void __run() {                                                               \
    const char *__class_name = #X;                                             \
    message("Test\n");

#define CPPUNIT_TEST_BODY(X)                                                   \
  {                                                                            \
    progress(__class_name, #X);                                                \
    try {                                                                      \
      X();                                                                     \
    } catch (...) {                                                            \
      error("Test Failed. An Exception was thrown.", #X, __FILE__, __LINE__);  \
    }                                                                          \
  }

#define CPPUNIT_TEST_END() }

#define CPPUNIT_FAIL                                                           \
  {                                                                            \
    test::__test_base::error("CPPUNIT_FAIL", "", __FILE__, __LINE__);          \
    return;                                                                    \
  }

#define CPPUNIT_ASSERT(X)                                                      \
  if (!(X)) {                                                                  \
    test::__test_base::error("CPPUNIT_ASSERT", #X, __FILE__, __LINE__);        \
    return;                                                                    \
  }

#define CPPUNIT_CHECK(X)                                                       \
  if (!(X)) {                                                                  \
    test::__test_base::error("CPPUNIT_CHECK", #X, __FILE__, __LINE__);         \
  }

#define CPPUNIT_TEST_REGISTRATION(X) static X static_##X;

#endif //__CPPUNIT_CPPUNIT_MINI__