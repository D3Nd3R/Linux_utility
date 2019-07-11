#ifndef PROC_UTILS_H
#define PROC_UTILS_H

#include <sys/types.h>

/**
 * @brief is_proc_run
 * @param proc_name
 * @return pid if process is running and -1 otherwise
 */
pid_t is_proc_run(char *proc_name);


#endif // PROC_UTILS_H
