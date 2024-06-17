#include <sys/wait.h>
#include "px_exit.h"
#include "px_types.h"

void	px_process__fork(t_process *process, t_program *program)
{
	process->pid = fork();
	if (process->pid == -1)
		px_exit("fork", program, process);
}

void	px_process__wait(t_process *process)
{
	waitpid(process->pid, NULL, 0);
}

t_process	*content(t_list *lst)
{
	return ((t_process *)lst->content);
}