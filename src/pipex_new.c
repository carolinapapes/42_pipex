/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 22:45:38 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/12 22:15:21 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "pipex.h"
#include "../libs/libft/libft.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "files_fd.h"
#include "files_fd.h"
#include "process.h"

t_cmd_new	*ft_allocate_cmd(t_cmd_new *cmd)
{
	cmd = (t_cmd_new *)malloc(sizeof(t_cmd_new));
	if (!cmd)
		return (NULL);
	cmd->str = NULL;
	cmd->arr = NULL;
	cmd->env = NULL;
	cmd->path = NULL;
	return (cmd);
}

void	ft_init_cmd(t_cmd_new *cmd, char *str, char **env)
{
	ft_allocate_cmd(cmd);
	if (!cmd)
		return ;
	cmd->str = str;
	cmd->arr = ft_split(str, ' ');
	cmd->env = env;
	cmd->path = command_path(str, env);
}

void	ft_open_files(int fd[2], int argc, char **argv)
{
	fd[READ_END] = open(argv[1], O_RDONLY);
	if (fd[READ_END] == -1)
		perror_msg(argv[1]);
	fd[WRITE_END] = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd[WRITE_END] == -1)
		perror_msg(argv[argc - 1]);
	printf("files opened\n");
}

void	ft_close_process_input_fds(t_process *process)
{
	if (process->input[READ_END] != -1)
		close(process->input[READ_END]);
	if (process->input[WRITE_END] != -1)
		close(process->input[WRITE_END]);
	process->input[READ_END] = -1;
	process->input[WRITE_END] = -1;
}

void	ft_wait_for_all(t_process *process)
{
	while (process)
		waitpid(process->pid, NULL, 0);
}

void	ft_manage_child(t_process *process, char *command, char **env)
{
	process_fds(process->input, process->output, FT_FD_INIT | FT_FD_DUP);
	if (process->input[READ_END] == -1)
		process_fds(process->input, process->output, FT_FD_ERROR | FT_FD_CLOSE);
	else
		command_call(command, env);
	process_fds(process->input, process->output, FT_FD_CLOSE);
	exit(0);
}

void	fork_process(t_process *process)
{
	process->pid = fork();
	if (process->pid == -1)
		perror_msg("fork");
}

int	pipex_new(t_program *program)
{
	int			i;
	t_list		*list;
	t_process	*process;

	i = -1;
	list = NULL;
	process = NULL;
	while (++i < program->cmdc - 1)
	{
		process = px_process(&list);
		if (!list || !process)
			return (1);
		io_set(list, program->fd_names, i == program->cmdc - 2);
		fork_process(process);
		if (process->pid == 0)
			ft_manage_child(process, program->cmdv[i], program->env);
		fd_close(process->input);
	}
	fd_close(process->output);
	return (0);
}
