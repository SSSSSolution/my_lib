#ifndef R_TIME_H
#define R_TIME_H

#include <chrono>
#include <string>

namespace r_common {

  class RTime {
  public:
    static std::string get_date();

    static std::string get_time_str_with_msec();
    static std::string get_time_str_with_nsec();

  };
}

#endif // R_TIME_H
