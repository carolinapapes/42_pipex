#ifndef PX_EXIT_H

# define PX_EXIT_H

# include "px_types.h"

void	program__free(t_program *program);
void	px_exit(char *msg, t_program *program, t_process *process);

#endif