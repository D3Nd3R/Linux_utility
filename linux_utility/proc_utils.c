#include "proc_utils.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE 512

pid_t is_proc_run(char *proc_name)
{
    DIR* procfs;

    if (!proc_name){
        return -1;
    }

    if (!(procfs = opendir("/proc"))){
        return -1;
    }

    struct dirent *dir = NULL;
    long cur_pid = -1;
    char* end_ptr = NULL;
    char cmd_buf[BUFF_SIZE];

    while ((dir = readdir(procfs))) {
        cur_pid = strtol(dir->d_name, &end_ptr, 10);
        if (*end_ptr != '\0' || cur_pid < 0){ continue; }
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
