# include "px_types.h"
# include <unistd.h>

void px_process__free(void *process)
{
	if	(process)
		free(process);
	return ;
}

void	px_process__fork(t_process *process)
{
	process->pid = fork();
	if (process->pid == -1)
		perror_msg("fork");
}

void	px_process__wait(t_process *process)
{
	waitpid(process->pid, NULL, 0);
}

// before exit this function must free program cmds or return
static void	px_process__allocate(t_process **process)
{
	*process = (t_process *)malloc(sizeof(t_process));
	if (*process)
		return ;
	// clean list and program and exit
	perror_msg("process allocation failed");
	return ;
}

static void	px_process__init(t_process *process)
{
	process->pid = -1;
	process->input[0] = -1;
	process->input[1] = -1;
	process->output[0] = -1;
	process->output[1] = -1;
	return ;
}

