/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 22:45:38 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/12 01:19:35 by carolinapap      ###   ########.fr       */
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

static void	process_init(t_process *process)
{
	process->pid = -1;
	process->input[0] = -1;
	process->input[1] = -1;
	process->output[0] = -1;
	process->output[1] = -1;
}

t_process	*ft_allocate_process(void)
{
	t_process	*process;

	process = (t_process *)malloc(sizeof(t_process));
	if (!process)
	{
		perror_msg("malloc");
		return (NULL);
	}
	process_init(process);
	return (process);
}

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

void	ft_print_process_data(t_process *process)
{
	printf("\n\npid: %d\ninput: read: %d write: %d\noutput: read: %d write: %d\ncmd: %s\ncmd path: %s\n\n", process->pid, process->input[READ_END], process->input[WRITE_END], process->output[READ_END], process->output[WRITE_END], process->cmd_new.str, process->cmd_new.path);
}

void	print_open_files(int *fd, char *call)
{
	printf("files opened by: %s\n read: %d\n write: %d\n", call, fd[READ_END], fd[WRITE_END]);
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

t_process	*create_process(t_list **list)
{
	t_process	*process;

	process = ft_allocate_process();
	if (!process)
		exit (1); //clean here
	ft_lstadd_back(list, ft_lstnew((void *)process));
	return (process);
}

void	fork_process(t_process *process)
{
	process->pid = fork();
	if (process->pid == -1)
		perror_msg("fork");
}

#define  struct s_program
{
	char	**cmdv;
	int		*cmdc;
	char	**env;
	int 	fd_names[2];
}

int	pipex_new(int argc, char **argv, char **env)
{
	t_list		*list;
	t_process	*process;
	int			i;
	int			fd[2];

	fd[READ_END] = argv[1];
	fd[WRITE_END] = argv[argc - 1];
	list = NULL;
	process = NULL;
	i = 1;
	while (++i < argc - 1)
	{
		process = create_process(&list);
		if (!list || !process)
			return (1);
		input_set(list, process, fd[READ_END], i == 2);
		output_set(process, fd[WRITE_END], i == argc - 2);
		fork_process(process);
		if (process->pid == 0)
			ft_manage_child(process, argv[i], env);
		fd_close(process->input);
	}
	fd_close(process->output);
	ft_lstclear(&list, free);
	return (0);
}
