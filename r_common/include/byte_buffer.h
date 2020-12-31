#ifndef REALITY_COMMON_BYTE_BUFFER_H
#define REALITY_COMMON_BYTE_BUFFER_H

#include <memory>

namespace reality
{
    namespace common
    {
        class File;
        class ByteBuffer
        {
        public:
            ByteBuffer();
            ~ByteBuffer();

//            template<typename T>
//            ByteBuffer& operator<<(T t);

//            template<>
//            ByteBuffer& operator<<(const File &f);

        private:
            struct Impl;
            std::unique_ptr<Impl> impl;
        };
    }
}

#endif
