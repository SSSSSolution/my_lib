#ifndef REALITY_WINDOW_INFO_H
#define REALITY_WINDOW_INFO_H

//#ifdef __cplusplus
//extern "C" {
//#endif

#include <X11/Xlib.h>

//#ifdef __cplusplus
//}
//#endif

namespace reality
{
namespace r_render_system
{
    class WindowInfo
    {
    public:
        WindowInfo() = default;
        ~WindowInfo() = default;
        Display *display;
        Window window;
    };
}
}




#endif
