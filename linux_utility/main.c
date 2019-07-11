#include <stdio.h>
#include <unistd.h>
#include "proc_utils.h"
#include "test.h"


int main(int argc, char **argv)
{
    is_proc_run("pam");
    test1("lin_util");

    return 0;
}
