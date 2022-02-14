#ifndef __CPPUNIT_FILE_REPORTER__
#define __CPPUNIT_FILE_REPORTER__

#include "cppunit_mini.h"
#include <cstdio>
#include <stdio.h>
namespace test {

class file_reporter : public __reporter_base {
public:
  file_reporter(char *file)
      : __num_error(0), __num_test(0), __is_my_stream(true) {
    __file = fopen(file, "w");
  }

  file_reporter(FILE *stream)
      : __num_error(0), __num_test(0), __is_my_stream(false) {
    __file = stream;
  }

  ~file_reporter() {
    if (__is_my_stream)
      fclose(__file);
    else
      fflush(__file);
  }

  void error(const char *__msg, const char *__function_name,
             const char *__in_file, int __in_line) {
    __num_error++;
    fprintf(__file, "\n\n%s(%d): %s(%s)\n", __in_file, __in_line,
            __function_name, __msg);
  }

  void message(const char *__msg) { fprintf(__file, "\n\t%s", __msg); }

  void progress(const char *__in_class_name, const char *__in_function_name) {
    __num_test++;
    fprintf(__file, "%s::%s\n", __in_class_name, __in_function_name);
  }
  void printSummary() {
    fprintf(__file, "\nerror %d / %d\n", __num_error, __num_test);
  }

private:
  int __num_error;
  int __num_test;
  bool __is_my_stream;
  FILE *__file;
};

} // namespace test

#endif //__CPPUNIT_FILE_REPORTER__
