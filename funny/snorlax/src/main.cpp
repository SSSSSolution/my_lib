#include <curses.h>
#include <signal.h>
#include <atomic>
#include <chrono>
#include <thread>

#include "frame.h"
/*
 *  sudo apt-get install ncurses-dev
 *  -lcurses
 */

using namespace reality::snorlax;
std::atomic<bool> run_loop;

void hander_sigint(int signum)
{
    if (signum == SIGINT)
    {
        printf("SIGIIO signal: %d\n", signum);
        run_loop = false;
    }
    else
    {
        printf("error\n");
    }
}

int main(int argc, char **argv)
{
    signal(SIGINT, hander_sigint);
    WINDOW *window = initscr();


    run_loop = true;
    int i = 0;
    while (run_loop)
    {
        Frame frame;
//        clear();
        move(0, 0);


        i++;
        auto str_list = frame.get_frame_content();
        std::string prt_str;
        for (auto str : str_list)
        {
            prt_str.append(str);
            prt_str.append(std::to_string(i));
            prt_str.append("\n");

        }
        printw(prt_str.c_str());
        refresh();
//        std::this_thread::sleep_for(std::chrono::milliseconds(50));

    }

    endwin();
    printf("stop\n");
    return 0;
}
