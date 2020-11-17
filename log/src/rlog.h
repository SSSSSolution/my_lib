#ifndef RLOG_H
#define RLOG_H

#define RLOG(severity, fmt, ...)   \
  do { \
    rlog::rlog_print(rlog::Severity::severity, #severity, __FILE__, __FUNCTION__, __LINE__, fmt"\n", __VA_ARGS__); \
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

void rlog_print(Severity severity_level, const char *severity, const char *file, const char *func, int line, const char *fmt, ...);

}



#endif // RLOG_H
