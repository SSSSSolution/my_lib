#include "rlog.h"
#include <stdio.h>

void test_rlog();

int main(int argc, char **argv)
{
    RLOG(TRACE, "info%s", "123");
    RLOG(ERROR, "open file %d failed!", 5);

    test_rlog();
    test_rlog();
    test_rlog();
    test_rlog();
    test_rlog();
    test_rlog();
    test_rlog();
    test_rlog();
    test_rlog();
    test_rlog();
    test_rlog();
    test_rlog();
    test_rlog();
    test_rlog();

    printf("hello!\n");
    return 0;
}


void test_rlog()
{
    RLOG(TRACE, "info%s", "123");
    RLOG(DEBUG, "open file %d failed!", 5);
}
