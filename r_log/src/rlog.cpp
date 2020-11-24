#include "rlog.h"
#include <stdarg.h>
#include <string>
#include <memory.h>
#include <iostream>

namespace rlog {

  Severity RLog::m_severity_level = TRACE;
  char RLog::m_buf[1024] = {0};
  FILE *RLog::m_fp = stdout;

  void RLog::set_severity_level(Severity s)
  {
    m_severity_level = s;
  }

  void RLog::set_target(FILE *fp)
  {
    if (fp == nullptr)
    {
      RLOG(ERROR, "Set RLog's target fp failed, fp is nullptr");
    } else {
      if (m_fp != stdout && m_fp != stderr)
        fclose(m_fp);
      m_fp = fp;
    }
  }

  void RLog::set_target(const char *file)
  {
    FILE *fp = fopen(file, "w");
    if (fp == nullptr)
    {
      RLOG(ERROR, "Set RLog's target file failed, can't open %s", file);
    } else {
      if (m_fp != stdout && m_fp != stderr)
        fclose(m_fp);
      RLOG(INFO, "set RLog's target file: %s", file);
      m_fp = fp;
    }
  }

  void RLog::print(Severity severity_level, const char *severity, const char *filepath,
                   const char *func, int line, const char *fmt, ...)
  {
    if (severity_level >= m_severity_level)
    {
      char *p = m_buf;
      std::string path = filepath;
      size_t pos = path.find_last_of('/');
      std::string filename(path.substr(pos+1));
      sprintf(p, "file<%s>, func<%s>, line<%d>, %s: ", filename.c_str(), func, line, severity);

      size_t offset = strlen(p);

      va_list args;
      va_start(args, fmt);
      vsprintf(p+offset, fmt, args);
      va_end(args);

      fprintf(m_fp, "%s\n", m_buf);
    }
  }

}
