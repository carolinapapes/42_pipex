#ifndef PX_EXIT_H

# define PX_EXIT_H

# include "px_types.h"

void	program__free(t_program *program);
void	px_exit(char *msg, t_program *program, t_process *process);
void	px_exit__127(char *msg, t_program *program, t_process *process);
void    px_exit__126(char *msg, t_program *program, t_process *process);
void	px_exit(char *msg, t_program *program, t_process *process);
void	px_free(t_program *program, t_process *process);
void    px_perror(char *msg);
void    px_perror__127(char *msg);

#endif