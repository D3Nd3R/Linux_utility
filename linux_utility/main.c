#include <stdio.h>
#include <unistd.h>
#include "proc_utils.h"
#include "test.h"


int main(int argc, char **argv)
{
#ifdef MY_TEST
    is_proc_run("pam");
    test1("lin_util");
    test2();
    test3();
    test4();
#endif
    return 0;
}
