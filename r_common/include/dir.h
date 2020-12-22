#ifndef REALITY_COMMON_DIR_H
#define REALITY_COMMON_DIR_H

#include <memory>
#include <string>
#include <vector>

namespace reality{
    namespace common {
    class Dir {
    public:
        Dir(std::string dir);
        ~Dir();

        bool exist();
        std::vector<std::string> sub_dirs();
        std::vector<std::string> sub_files();
        std::vector<std::string> sub_dirs_and_files();

    private:
        struct Impl;
        std::unique_ptr<Impl> m_impl;
    };
    }
}



#endif
