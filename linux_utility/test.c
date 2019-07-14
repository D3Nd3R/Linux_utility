#include "test.h"
#ifdef MY_TEST
#include <assert.h>
#include <stdio.h>

#include "proc_utils.h"


void test1(char *proc_name)
{
    assert(is_proc_run(proc_name) > 0);
    printf("Test 1 DONE\n");

    assert(is_proc_run("-1") < 0);
    printf("Test 1.1 DONE\n");

}

void test2()
{
    char *strs[] = {"one", "two", "three", NULL};

    str_llist_t *head = __create_str_llist(strs);
    assert(head);
    printf("%s\n", "str_llist_t *head = create_str_llist(strs)");
    __print_llist(head);
    __delete_std_llist(&head);
    assert(!head);
    printf("%s\n", "delete_std_llist(&head);");
    __print_llist(head);

    printf("TEST 2 DONE\n");
}

void test3()
{
    char *strs[] = {"one", "two", "three", "four", "five", NULL};

    str_llist_t *head = __create_str_llist(strs);
    assert(head);
    printf("%s\n", "str_llist_t *head = create_str_llist(strs)");

    __print_llist(head);

    __del_node_by_str(&head, "one");
    __print_llist(head);

    __del_node_by_str(&head, "three");
    __print_llist(head);

    __del_node_by_str(&head, "five");
    __print_llist(head);

    __del_node_by_str(&head, "sdfsdfsdf");
    __print_llist(head);

    __delete_std_llist(&head);
    printf("TEST 3 DONE\n");
}

void test4()
{
    char *procs1[] = {"vlc", "qtcreator", "firefox", NULL};
    int res = is_procs_run(procs1);
    assert(res == 0);

    char *proc2[] = {"sdfsdf", "sdf", NULL};
    res = is_procs_run(proc2);
    assert(res != 0);

    char *proc3[] = {"vlc", "qtcreator", "sdfsdf", "sdf", NULL};
    res = is_procs_run(proc3);
    assert(res != 0);
    printf("TEST 4 DONE\n");
}

void test5()
{
    assert(!is_kmodule_load("vboxdrv"));
    assert(is_kmodule_load("sdfsfsdf"));
    printf("TEST 5 DONE\n");
}
#endif //MY_TEST



void test6()
{
    char *kmod1[] = {"ip_tables", "ip6_tables", "vboxnetadp",
                     "edac_mce_amd", NULL};
    assert(!is_kmodules_load(kmod1));

    char *kmod2[] = {"ip_tables", "ip6_tables", "fsdfsdfdfs",
                     "vboxnetadp", "edac_mce_amd", NULL};
    assert(is_kmodules_load(kmod2));
    printf("TEST 6 DONE\n");
}
