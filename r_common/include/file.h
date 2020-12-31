#ifndef REALITY_R_COMMON_FILE_H
#define REALITY_R_COMMON_FILE_H

#include <string>
#include <memory>

namespace reality {
    namespace common {
        class File
        {
        public:
            File(const std::string &file_path);
            ~File();

            std::string absolute_path();
            bool exist();
            bool copy(std::string dst_file);
            bool remove();
            void sync();


        private:
            struct Impl;
            std::unique_ptr<Impl> impl;
        };
    }
}

#endif
