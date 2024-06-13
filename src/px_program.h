#ifndef PX_PROGRAM_H

# define PX_PROGRAM_H
# include "px_types.h"

void   px_program__free(t_program *program);
void   px_program(t_program *program, int argc, char **argv, char **env);
int    pipex_new(t_program *program);

#endif
