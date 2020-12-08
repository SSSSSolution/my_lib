#include "r_window.h"

int main(int argc, char *argv[])
{
    reality::r_render_system::RWindow window;
    window.init(1600, 1600, 0, 0);
    window.show();
    return 0;
}
