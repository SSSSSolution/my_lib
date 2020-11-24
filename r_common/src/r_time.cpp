#include "r_time.h"
#include <ctime>

namespace r_common {

  using sys_clock_t_ = std::chrono::system_clock;

  std::string RTime::get_date()
  {
    std::time_t st = sys_clock_t_::to_time_t(sys_clock_t_::now());
    std::string ts = std::ctime(&st);
    ts.resize(ts.size()-1);
    return ts;
  }

  std::string RTime::get_time_str_with_msec()
  {

  }
}
