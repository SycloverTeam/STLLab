
#include "cppunit_mini.h"
#include "cppunit_until.h"
#include "file_reporter.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  test::file_reporter *fr = new test::file_reporter(stdout);
  test::__test_base::set_reporter(fr);

  test::__test_base *test;
  test = test_root;
  for (; test;) {
    test->__run();
    test = test->next;
  }
  fr->printSummary();
  return 0;
}