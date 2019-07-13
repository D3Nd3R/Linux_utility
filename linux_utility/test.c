#include "test.h"

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

    str_llist_t *head = create_str_llist(strs);
    assert(head);
    printf("%s\n", "str_llist_t *head = create_str_llist(strs)");
    print_llist(head);
    delete_std_llist(&head);
    assert(!head);
    printf("%s\n", "delete_std_llist(&head);");
    print_llist(head);

    printf("TEST 2 DONE\n");
}

void test3()
{
    char *strs[] = {"one", "two", "three", "four", "five", NULL};

    str_llist_t *head = create_str_llist(strs);
    assert(head);
    printf("%s\n", "str_llist_t *head = create_str_llist(strs)");

    print_llist(head);

    del_node_by_str(&head, "one");
    print_llist(head);

    del_node_by_str(&head, "three");
    print_llist(head);

    del_node_by_str(&head, "five");
    print_llist(head);

    del_node_by_str(&head, "sdfsdfsdf");
    print_llist(head);

    delete_std_llist(&head);
    printf("TEST 3 DONE\n");
}
