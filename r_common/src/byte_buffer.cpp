#include "byte_buffer.h"

namespace reality
{
    namespace common
    {
        struct ByteBuffer::Impl
        {
            void *data;

        };

        ByteBuffer::ByteBuffer()
        {

        }

        ByteBuffer::~ByteBuffer() = default;
    }
}
