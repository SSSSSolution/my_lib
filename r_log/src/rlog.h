#ifndef RLOG_H
#define RLOG_H
extern "C" {
#include <stdio.h>
}
#define RLOG(severity, fmt, ...)                                            \
  do {                                                                      \
    rlog::RLog::print(rlog::Severity::severity,                             \
      #severity, __FILE__, __FUNCTION__, __LINE__, fmt, ## __VA_ARGS__);    \
  } while(0)

namespace rlog {
// https://stackoverflow.com/questions/2031163/when-to-use-the-different-log-levels
  enum Severity {
    TRACE,
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL,
  };

  class RLog
  {
  public:
    static void set_severity_level(Severity s);
    static void set_target(FILE *fp);
    static void set_target(const char *filename);

    static void print(Severity severity_level, const char *severity, const char *file,
               const char *func, int line, const char *fmt, ...);


  private:
    static Severity    m_severity_level;
    static char        m_buf[1024];
    static FILE        *m_fp;
  };

}

#endif // RLOG_H





















