#include "rlog.h"
#include <stdio.h>
#include <stdarg.h>
#include <string>
#include <memory.h>

namespace rlog {

char buf[1024];
void rlog_print(Severity severity_level, const char *severity, const char *filepath, const char *func, int line, const char *fmt, ...)
{
    char *p = buf;
    std::string path = filepath;
    size_t pos = path.find_last_of('/');
    std::string filename(path.substr(pos+1));
    sprintf(p, "file<%s>, func<%s>, line<%d>, %s: ", filename.c_str(), func, line, severity);

    size_t offset = strlen(p);

    va_list args;
    va_start(args, fmt);
    vsprintf(p+offset, fmt, args);
    va_end(args);

    fprintf(stdout, buf);
}

}
