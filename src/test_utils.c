#include "pipex.h"

void	ft_print_process_data(t_process *process)
{
	printf("\n\npid: %d\ninput: read: %d write: %d\noutput: read: %d write: %d\ncmd: %s\ncmd path: %s\n\n", process->pid, process->input[READ_END], process->input[WRITE_END], process->output[READ_END], process->output[WRITE_END], process->cmd_new.str, process->cmd_new.path);
}

void	print_open_files(int *fd, char *call)
{
	printf("files opened by: %s\n read: %d\n write: %d\n", call, fd[READ_END], fd[WRITE_END]);
}