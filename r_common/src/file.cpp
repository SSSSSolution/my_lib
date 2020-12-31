#include "file.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fstream>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

namespace reality
{
namespace common {
    struct File::Impl
    {
        std::string m_file;
    };

    File::File(const std::string &file_path)
        : impl(new Impl())
    {
       impl->m_file = file_path;
    }

    File::~File()
    {

    }

    std::string File::absolute_path()
    {
        if (!exist())
        {
            return std::string();
        }
        auto path_max = pathconf(impl->m_file.c_str(), _PC_PATH_MAX);
        if (path_max < 0)
            path_max = 4096;
        char abs_path[static_cast<uint32_t>(path_max)];
        return realpath(impl->m_file.c_str(), abs_path);
    }

    bool File::exist()
    {
        struct stat s;
        auto ret = stat(impl->m_file.c_str(), &s);
        return (ret == 0);
    }

    bool File::copy(std::string dst_file)
    {
        File dst(dst_file);
        if (absolute_path() == dst.absolute_path())
        {
            return false;
        }
        std::ifstream in(impl->m_file);
        std::ofstream out(dst_file);
        if (in.good() && out.good())
        {
            out << in.rdbuf();
            return true;
        }
        else {
           return false;
        }
    }

    bool File::remove()
    {
        if (std::remove(absolute_path().c_str()) == 0)
        {
            return true;
        }
        return false;
    }

    void File::sync()
    {
        int fd = open(absolute_path().c_str(), O_SYNC);
        fdatasync(fd);
        close(fd);
    }


}
}
