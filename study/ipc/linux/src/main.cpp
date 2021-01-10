#include <stdio.h>
#include <mqueue.h>
#include <iostream>
#include <errno.h>
#include <unistd.h>
int main(int argc, char **argv)
{

    const char *name = "/memAvailMsgQ";
    mq_unlink(name);
    struct mq_attr attr;
//    attr.mq_maxmsg = 20;
//    attr.mq_msgsize = 50;
    mqd_t mqd = mq_open(name, O_RDWR | O_CREAT | O_EXCL, 0644, nullptr);
    std::cout << name << std::endl;
    if (mqd == -1)
    {
        std::cout << "mqd open error: " << mqd << std::endl;
        perror("open mq failed");
    }

    mq_getattr(mqd, &attr);

    std::cout << "default maxmsg: " << attr.mq_maxmsg << std::endl;
    std::cout << "default msgsize: " << attr.mq_msgsize << std::endl;


    mq_close(mqd);
    return 0;
}
