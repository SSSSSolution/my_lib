#include "dir.h"
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

namespace reality
{
namespace common {

    static bool is_dir(const char *dir_name)
    {
        struct stat s;
        lstat(dir_name, &s);
        if (!S_ISDIR(s.st_mode))
        {
            return false;
        }

        return true;
    }

    static bool is_file(const char *file_name)
    {
        struct stat s;
        lstat(file_name, &s);
        if (!S_ISREG(s.st_mode))
        {
            return false;
        }

        return true;
    }

    struct Dir::Impl {
        std::string m_dir;

        bool exist()
        {
            return is_dir(m_dir.c_str());
        }

        std::vector<std::string> sub_dirs()
        {
            std::vector<std::string> result;
            if (!exist())
            {
                return result;
            }

            DIR *dir;
            dir = opendir(m_dir.c_str());
            if (dir == nullptr)
            {
                printf("Cannot open dir %s\n", m_dir.c_str());
                return result;
            }

            struct dirent *filename;
            while ((filename = readdir(dir)) != nullptr)
            {
                if (strcmp(filename->d_name, ".") == 0 ||
                    strcmp(filename->d_name, "..") == 0)
                {
                    continue;
                }

                std::string sub_dir;
                sub_dir.append(m_dir).append("/").append(filename->d_name);
                if (is_dir(sub_dir.c_str()))
                {
                    result.push_back(filename->d_name);
                }
            }
            closedir(dir);

            return result;
        }
        std::vector<std::string> sub_files()
        {
            std::vector<std::string> result;
            if (!exist())
            {
                return result;
            }

            DIR *dir;
            dir = opendir(m_dir.c_str());
            if (dir == nullptr)
            {
                printf("Cannot open dir %s\n", m_dir.c_str());
                return result;
            }

            struct dirent *filename;
            while ((filename = readdir(dir)) != nullptr)
            {
                std::string sub_file;
                sub_file.append(m_dir).append("/").append(filename->d_name);
                if (is_file(sub_file.c_str()))
                {
                    result.push_back(filename->d_name);
                }
            }
            closedir(dir);

            return result;
        }
        std::vector<std::string> sub_dirs_and_files()
        {
            auto dirs = sub_dirs();
            auto files = sub_files();

            for (auto f : files)
            {
                dirs.push_back(f);
            }
            return dirs;
        }
    };

    Dir::Dir(std::string dir) : m_impl(new Impl())
    {
        m_impl->m_dir = dir;
    }

    Dir::~Dir() = default;

    bool Dir::exist()
    {
        return m_impl->exist();
    }

    std::vector<std::string> Dir::sub_dirs()
    {
        return m_impl->sub_dirs();
    }

    std::vector<std::string> Dir::sub_files()
    {
        return m_impl->sub_files();
    }

    std::vector<std::string> Dir::sub_dirs_and_files()
    {
        return m_impl->sub_dirs_and_files();
    }
}
}
