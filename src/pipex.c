/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:58:07 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/12 20:05:43 by carolinapap      ###   ########.fr       */
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

int	is_forked(int *pid)
{
	*pid = fork();
	return (*pid >= 0);
}

void	pipe_init(t_pipe *s_pipe)
{
	s_pipe->pid_in = -1;
	s_pipe->pid_out = -1;
	s_pipe->fd_outside[READ_END] = STDIN_FILENO;
	s_pipe->fd_outside[WRITE_END] = STDOUT_FILENO;
	s_pipe->fd_inside[READ_END] = -1;
	s_pipe->fd_inside[WRITE_END] = -1;
}

void	open_outfiles(int *fd, int argc, char **argv)
{
	fd[READ_END] = open(argv[1], O_RDONLY);
	if (fd[READ_END] == -1)
		perror_msg(argv[1]);
	fd[WRITE_END] = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd[WRITE_END] == -1)
		perror_msg(argv[argc - 1]);
}

void	open_infiles(int *fd, t_pipe *s_pipe)
{
	if (pipe(fd) < 0)
	{
		perror_msg("pipe");
		fd_close(s_pipe->fd_outside);
		exit(1);
	}
}

void	pipe_initialize(t_pipe *s_pipe, int argc, char **argv)
{
	pipe_init(s_pipe);
	open_outfiles(s_pipe->fd_outside, argc, argv);
	open_infiles(s_pipe->fd_inside, s_pipe);
}

int	pipex(int argc, char **argv, char **env)
{
	t_pipe	s_pipe;
	int		is_fork;

	pipe_initialize(&s_pipe, argc, argv);
	if (!is_forked(&s_pipe.pid_in))
		return (1);
	if (s_pipe.pid_in == 0)
		return (process_child(s_pipe.fd_outside, s_pipe.fd_inside, argv[2], env));
	is_fork = is_forked(&s_pipe.pid_out);
	if (is_fork && s_pipe.pid_out == 0)
		return (process_child(s_pipe.fd_inside, s_pipe.fd_outside, argv[3], env));
	fd_close(s_pipe.fd_inside);
	fd_close(s_pipe.fd_outside);
	waitpid(s_pipe.pid_in, NULL, 0);
	is_fork && waitpid(s_pipe.pid_out, s_pipe.signal_out, 0);
	if (is_fork && WIFEXITED(*s_pipe.signal_out))
		return (WEXITSTATUS(*s_pipe.signal_out));
	return (0);
}
