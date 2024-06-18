

#include "../include/px_types.h"
#include "../include/px_process.h"
#include "../include/px_exit.h"
#include <sys/wait.h>

static void	wait__check(t_process *process)
{
	if (process && process->pid != -1)
		waitpid(process->pid, NULL, 0);
}

void	px_process__wait(t_program *program)
{
	int			status;
	int			exit_status;
	t_process 	*process;

	process = content(program->list);
	program->list->content = NULL;
	ft_lstiter(program->list, (void *)wait__check);
	waitpid(process->pid, &status, 0);
	px_free(program, process);
	exit_status = WEXITSTATUS(status);
	exit (exit_status);
}