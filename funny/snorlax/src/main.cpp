#include <curses.h>
#include <signal.h>
#include <atomic>
#include <chrono>
#include <thread>
/*
 *  sudo apt-get install ncurses-dev
 *  -lcurses
 */

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

    chtype str[100];
    std::string hello_str("Hello, curses");
    for (size_t i = 0; i < hello_str.size(); i++)
    {
        str[i] = hello_str[i];
    }

    run_loop = true;
    while (run_loop)
    {
        clear();
        box(window, '*', '-');
        move(1, 1);
        addchstr(str);
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

    }

    endwin();
    printf("stop\n");
    return 0;
}
