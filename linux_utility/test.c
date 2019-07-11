#include "test.h"

#include <assert.h>
#include <stdio.h>

#include "proc_utils.h"


void test1(char *proc_name)
{
    assert(is_proc_run(proc_name) > 0);
    printf("Test 1 DONE\n");


    assert(is_proc_run("-1") < 0);
    printf("Test 2 DONE\n");

}
