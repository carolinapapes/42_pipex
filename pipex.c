/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:58:07 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/05 20:56:57 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "pipex.h"
#include "./libs/libft/libft.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

int	is_forked(int *pid)
{
	*pid = fork();
	return (*pid >= 0);
}

void	pipe_init(int argc, char **argv, t_pipe *s_pipe)
{
	s_pipe->pid = -1;
	s_pipe->pid_2 = -1;
	s_pipe->inout_fd[READ_END] = open(argv[1], O_RDONLY);
	if (s_pipe->inout_fd[READ_END] == -1)
		perror(ft_strjoin((char *const)&"pipex: ", argv[1]));
	s_pipe->inout_fd[WRITE_END] = open(argv[argc - 1], \
		O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (s_pipe->inout_fd[WRITE_END] == -1)
		perror(ft_strjoin((char *const)&"pipex: ", argv[argc - 1]));
	s_pipe->fd[READ_END] = -1;
	s_pipe->fd[WRITE_END] = -1;
}

void	pipe_close(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

int	process_child(int *pipe_read, int *pipe_write, char *command, char **envp)
{
	int	i;

	close(pipe_read[WRITE_END]);
	close(pipe_write[READ_END]);
	if (pipe_read[READ_END] == -1 || pipe_write[WRITE_END] == -1)
		exit(1);
	dup2(pipe_read[READ_END], STDIN_FILENO);
	dup2(pipe_write[WRITE_END], STDOUT_FILENO);
	i = command_exec(command, envp);
	close(pipe_read[READ_END]);
	close(pipe_write[WRITE_END]);
	exit(i);
}

int	pipex(int argc, char **argv, char **envp)
{
	t_pipe	s_pipe;
	int		is_fork;

	pipe_init(argc, argv, &s_pipe);
	if (pipe(s_pipe.fd) < 0)
		exit(1);
	if (!is_forked(&s_pipe.pid))
		return (1);
	if (s_pipe.pid == 0)
		return (process_child(s_pipe.inout_fd, s_pipe.fd, argv[2], envp));
	is_fork = is_forked(&s_pipe.pid_2);
	if (is_fork && s_pipe.pid_2 == 0)
		return (process_child(s_pipe.fd, s_pipe.inout_fd, argv[3], envp));
	pipe_close(s_pipe.fd);
	waitpid(s_pipe.pid, NULL, 0);
	is_fork && waitpid(s_pipe.pid_2, s_pipe.pid_signal, 0);
	pipe_close(s_pipe.inout_fd);
	if (is_fork && WIFEXITED(*s_pipe.pid_signal))
		return (WEXITSTATUS(*s_pipe.pid_signal));
	return (1);
}
