#ifndef REALITY_APP_PANDA_UTIL_H
#define REALITY_APP_PANDA_UTIL_H

#include <string>
namespace reality {


    bool check_date(int year, int mon, int day);
    std::string get_file_name_by_date(std::string suffix, int year, int mon, int day);
    std::string get_dir_by_date(std::string root_dir, int year, int mon);
    std::string get_file_path_by_date(std::string root_dir, std::string suffix, int year, int mon, int day);

    std::string get_home_dir();
    int open_file_with_editor(std::string file, std::string editor);
}

#endif
