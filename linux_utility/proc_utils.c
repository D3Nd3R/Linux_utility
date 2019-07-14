#include "proc_utils.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE 512

pid_t is_proc_run(char *proc_name)
{
    if (!proc_name){ return -1; }

    DIR* procfs;
    if (!(procfs = opendir("/proc"))){ return -1; }

    struct dirent *dir = NULL;
    long cur_pid = -1;
    char* end_ptr = NULL;
    char cmd_buf[BUFF_SIZE];

    while ((dir = readdir(procfs))) {
        cur_pid = strtol(dir->d_name, &end_ptr, 10);
        if (*end_ptr != '\0' || cur_pid < 0 || cur_pid == 0){ continue; }
        snprintf(cmd_buf, BUFF_SIZE, "/proc/%ld/stat", cur_pid);

        FILE *fp_stat = fopen(cmd_buf, "r");
        if (!fp_stat){ continue; }
        if ((fscanf(fp_stat,"%ld (%[^)])", &cur_pid, cmd_buf)) != 2){
            fclose(fp_stat);
            continue;
        }
        if (!strcmp(proc_name, cmd_buf)){
            fclose(fp_stat);
            closedir(procfs);
            return (pid_t)cur_pid;
        }

        fclose(fp_stat);
    }

    closedir(procfs);
    return -1;
}

#ifndef MY_TEST
typedef struct str_llist
{
    char *str;
    struct str_llist *p_next;

} str_llist_t;

typedef str_llist_t node;
#endif //MY_TEST

node* __push_node(node *head, char *str)
{
    node *new = (node *) malloc(sizeof(node));
    new->str = strdup(str);
    new->p_next = NULL;

    if (head == NULL){
        head = new;
    }
    else {
        node *it;
        for (it = head; it->p_next != NULL; it = it->p_next);
        it->p_next = new;
    }

    return head;
}

str_llist_t* __create_str_llist(char **strs)
{
    if (!strs || !*strs){ return NULL; }

    str_llist_t *head;

    head = __push_node(NULL, *strs);
    ++strs;

    while (*strs) {
        __push_node(head, *strs);
        ++strs;
    }
    return head;
}

node* __find_node_str(node *head, char *str)
{
    if (!head || !str){ return NULL; }
    while (head) {
        if (!strcmp(head->str, str)){ return head; }
    }
    return NULL;
}


void __delete_std_llist(node **head)
{
    if (!head || !*head){return;}

    node *it = *head;
    node *next;
    while(it){
        next = it->p_next;
        if (it->str){free(it->str);}
        free(it);
        it = next;
    }
    *head = NULL;
}

#ifdef MY_TEST
void __print_llist(node *head)
{
    while (head) {
        printf("%s\n",head->str);
        head = head->p_next;
    }
    printf("\n");
}
#endif //MY_TEST


void __del_node_by_str(node **head, char* str)
{
    if (!head || !*head || !str){ return; }

    node *prev, *cur;
    prev = NULL;

    for (cur = *head; cur != NULL; prev = cur, cur = cur->p_next){
        if(strcmp(cur->str,str)){ continue; }
        if (prev == NULL) {
            *head = cur->p_next;
        }else {
            prev->p_next = cur->p_next;
        }
        free(cur->str);
        free(cur);
    }
}



int is_procs_run(char **procs)
{
    if (!procs || !*procs){ return -1; }

    DIR* procfs;
    if (!(procfs = opendir("/proc"))){ return -1; }

    struct dirent *dir = NULL;
    long cur_pid = -1;
    char* end_ptr = NULL;
    char buf[BUFF_SIZE];
    node* head = __create_str_llist(procs);
    node* iter = head;

    while ((dir = readdir(procfs))) {
        cur_pid = strtol(dir->d_name, &end_ptr, 10);
        if (*end_ptr != '\0' || cur_pid < 0 || cur_pid == 0){ continue; }
        snprintf(buf, BUFF_SIZE, "/proc/%ld/stat", cur_pid);

        FILE *fp_stat = fopen(buf, "r");
        if (!fp_stat){ continue; }
        if ((fscanf(fp_stat,"%ld (%[^)])", &cur_pid, buf)) != 2){
            fclose(fp_stat);
            continue;
        }
        if (!head) { return 0; }
        iter = head;
        while (iter) {
            if (strcmp(iter->str, buf)){
                iter = iter->p_next;
                continue;
            }
            __del_node_by_str(&head,iter->str);
            break;
        }
        fclose(fp_stat);
    }

    closedir(procfs);
    if (!head){
        return 0;
    }

    __delete_std_llist(&head);
    return -1;
}



