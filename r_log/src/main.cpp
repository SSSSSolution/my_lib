#include "rlog.h"
#include <stdio.h>

void test_basic_print();
void test_severity_level(rlog::Severity s);
void test_target_fp(FILE *fp);
void test_target_file(const char *filename);

int main(int argc, char **argv)
{ 
  (void)argc;
  (void)argv;

  printf("rlog: test basic log\n");
  test_basic_print();

  printf("rlog: test TRACE log\n");
  test_severity_level(rlog::TRACE);
  printf("rlog: test DEBUG log\n");
  test_severity_level(rlog::DEBUG);
  printf("rlog: test INFO log\n");
  test_severity_level(rlog::INFO);
  printf("rlog: test WARN log\n");
  test_severity_level(rlog::WARN);
  printf("rlog: test ERROR log\n");
  test_severity_level(rlog::ERROR);
  printf("rlog: test FATAL log\n");
  test_severity_level(rlog::FATAL);

  rlog::RLog::set_severity_level(rlog::TRACE);
  printf("rlog: test stderr log\n");
  test_target_fp(stderr);
  printf("rlog: test stdout log\n");
  test_target_fp(stdout);
  printf("rlog: test /tmp/rlog_test.log log\n");
  test_target_file("/tmp/rlog_test.log");
}

void test_basic_print()
{
  RLOG(TRACE, "trace %s", "info");
  RLOG(DEBUG, "debug %s", "info");
  RLOG(INFO,  "info %s", "info");
  RLOG(WARN,  "warn %s", "info");
  RLOG(ERROR, "error %s", "info");
  RLOG(FATAL, "fatal %s", "info");
}

void test_severity_level(rlog::Severity s)
{
  rlog::RLog::set_severity_level(s);
  test_basic_print();
}

void test_target_fp(FILE *fp)
{
  rlog::RLog::set_target(fp);
  test_basic_print();
}

void test_target_file(const char *filename)
{
  rlog::RLog::set_target(filename);
  test_basic_print();
}
