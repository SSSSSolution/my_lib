#include "r_renderer.h"
#include <memory>
#include "r_window.h"
#include <iostream>

using namespace reality::r_render_system;
int main(int argc, char *argv[])
{
    std::shared_ptr<RWindow> window(new RWindow());
    std::cout << sizeof(window) << std::endl;
    window->init(1600, 1600, 0, 0);
    std::shared_ptr<RRenderer> renderer(new RRenderer(window));
    renderer->init();
    window->show();

    return 0;
}
