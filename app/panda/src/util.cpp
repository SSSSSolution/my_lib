#include "util.h"
#include <time.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

namespace reality
{
    bool check_date(int year, int mon, int day)
    {
        if (mon <= 0 || mon > 12)
        {
            printf("invalid month: %d\n", mon);
            return false;
        }

        if (day <= 0 || day > 31)
        {
            printf("invalid day: %d\n", day);
            return false;
        }

        return true;
    }

    std::string get_file_name_by_date(std::string suffix, int year, int mon, int day)
    {
        if (!check_date(year, mon, day))
        {
            printf("cannot get file by name: year = %d, mon = %d, day = %d\n",
                   year, mon, day);
            exit(-1);
        }

        std::string y = std::to_string(year);
        std::string m = std::to_string(mon);
        std::string d = std::to_string(day);

        std::string name;
        return  name.append(y).append(m).append(d).append(".").append(suffix);
    }

    std::string get_dir_by_date(std::string root_dir, int year, int mon)
    {
        if (!check_date(year, mon, 1))
        {
            printf("cannot get file by name: year = %d, mon = %d\n",
                   year, mon);
            exit(-1);
        }

        std::string dir;
        std::string y = std::to_string(year);
        std::string m = std::to_string(mon);

        return dir.append(root_dir).append("/").
                append(y).append("/").append(m);
    }

    std::string get_file_path_by_date(std::string root_dir, std::string suffix, int year, int mon, int day)
    {
        std::string path;

        std::string dir = get_dir_by_date(root_dir, year, mon);
        std::string name = get_file_name_by_date(suffix, year, mon, day);

        return path.append(dir).append("/").append(name);
    }

    std::string get_home_dir()
    {
        struct passwd *pw = getpwuid(getuid());
        const char *home_dir = pw->pw_dir;
        return std::string(home_dir);
    }

    int open_file_with_editor(std::string file, std::string editor)
    {
        std::string cmd;
        cmd.append(editor).append(" ").append(file);
        return system(cmd.c_str());
    }
}



























