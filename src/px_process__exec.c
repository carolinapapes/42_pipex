#include "pipex.h"
#include "px_exit.h"
#include "px_fd.h"
#include "px_types.h"
#include "px_process.h"

void	px_exec__clean( t_process **process, t_program **program, char *cmd)
{
	*process = content((*program)->list);
	(*program)->list->content = NULL;
	(*process)->cmd = NULL;
	(*process)->cmd_str = cmd;
	program__free(*program);
}

// void	px_child(t_process *process, char *command, char **env)
void	px_process__exec(t_program *program, char *cmd)
{
	t_process	*process;

	px_exec__clean(&process, &program, cmd);
	px_fd__handler(process->input, process->output, FT_FD_INIT | FT_FD_DUP);
	if (process->input[READ_END] >= 0)
		px_cmd(process, program->env);
	px_fd__handler(process->input, process->output, FT_FD_CLOSE);
	px_exit(cmd, program, process);
}