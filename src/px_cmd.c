/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 23:18:11 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/16 08:55:41 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/libft/libft.h"
#include <stdio.h>
#include <string.h>
#include "pipex.h"
#include "px_types.h"
#include "px_exit.h"
#include <errno.h>


static void	path__concat(char *name, char *partial_path, char **path, t_process *process)
{
	char	*tmp;

	tmp = ft_strjoin(partial_path, "/");
	if (!tmp)
		px_exit("path__concat ft_strjoin failed", NULL, process);
	*path = ft_strjoin(tmp, name);
	if (!*path)
		px_exit("path__concat ft_strjoin failed", NULL, process);
	free(tmp);
	tmp = NULL;
}

static void	paths__get(char *name, char **path, char **paths__arr, t_process *process)
{
	int			i;

	i = -1;
	path__concat(name, paths__arr[++i], path, process);
	while (access(*path, R_OK) && paths__arr[++i])
	{
		free(*path);
		*path = NULL;
		path__concat(name, paths__arr[i], path, process);
	}
	if (!paths__arr[i])
	{
		free(*path);
		*path = ft_strdup(name);
		if (!*path)
			px_exit("paths__get ft_strdup failed", NULL, process);
	}
}

static void	cmd__path(t_process *process)
{
	const char	*paths__str;
	char		**paths__arr;
	t_cmd		*cmd;

	cmd = process->cmd;
	cmd->path = NULL;
	paths__str = ft_str__find(cmd->env, "PATH=");
	paths__arr = ft_split(paths__str, ':');
	if (!paths__arr)
		px_exit("cmd_path", NULL, process);
	paths__get(cmd->arr[0], &cmd->path, paths__arr, process);
	ft_split__free(paths__arr);
}

// close fds ?
static void	cmd__arr(t_process *process, char separator)
{
	process->cmd->arr = ft_split(process->cmd_str, separator);
	if (!(process->cmd->arr))
		px_exit("ft_split", NULL, process);
}

static void	px_cmd__init(t_process *process, char **env)
{
	(process->cmd)->str = process->cmd_str;
	process->cmd->env = env;
	cmd__arr(process, ' ');
	cmd__path(process);
}

void	px_cmd(t_process *process, char **env)
{
	t_cmd	cmd;

	process->cmd = &cmd;
	px_cmd__init(process, env);
	execve(cmd.path, cmd.arr, env);
	strerror(errno);
	px_exit(cmd.path, NULL, process);
}
