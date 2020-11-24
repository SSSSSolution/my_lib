#include "r_time.h"
#include <iostream>

int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;

  std::cout << r_common::RTime::get_date() << std::endl;
  std::cout << r_common::RTime::get_date() << std::endl;
}
