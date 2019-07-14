#ifndef PROC_UTILS_H
#define PROC_UTILS_H

#include <sys/types.h>

/**
 * @brief is_proc_run
 * @param proc_name
 * @return pid if process is running and -1 otherwise
 */
pid_t is_proc_run(char *proc_name);


/**
 * @brief is_procs_run check sevaral process
 * @param procs
 * @return 0 if all process are running and -1 othrewise
 */
int is_procs_run(char **procs);

#ifdef MY_TEST

typedef struct str_llist
{
    char *str;
    struct str_llist *p_next;

} str_llist_t;

typedef str_llist_t node;

str_llist_t* __create_str_llist(char **strs);
node* __push_node(node *head, char *str);
void __delete_std_llist(node **head);
void __print_llist(node *head);
void __del_node_by_str(node **head, char *str);
node *__find_node_str(node *head, char *str);

#endif //MY_TEST

#endif // PROC_UTILS_H
