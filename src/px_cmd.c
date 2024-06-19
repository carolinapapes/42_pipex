/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 23:18:11 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/19 22:38:07 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/libft/libft.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "../include/pipex.h"
#include "../include/px_types.h"
#include "../include/px_process.h"
#include "../include/px_exit.h"

static	void	is_dir(char *name, t_process *process)
{
	int			fd;

	fd = open(name, O_DIRECTORY);
	if (fd == -1)
		return ;
	close(fd);
	if (errno == EINVAL)
		errno = EISDIR;
	px_exit(name, NULL, process);
}

static char	*is_path(char *name, char **path, t_process *process)
{
	if (ft_strchr(name, '/'))
	{
		is_dir(name, process);
		*path = ft_strdup(name);
		if (!*path)
			px_exit("paths__get ft_strdup failed", NULL, process);
	}
	return (*path);
}

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
	while (access(*path, X_OK) && paths__arr[++i])
	{
		free(*path);
		*path = NULL;
		path__concat(name, paths__arr[i], path, process);
	}
	if (paths__arr[i])
	{
		return ;
	}
	free(*path);
	*path = NULL;
	px_exit__127(name, NULL, process);
}

static void	cmd__path(t_process *process)
{
	const char	*paths__str;
	char		**paths__arr;
	t_cmd		*cmd;

	cmd = process->cmd;
	cmd->path = NULL;
	if (is_path(cmd->arr[0], &cmd->path, process))
		return ;
	paths__str = ft_str__find(cmd->env, "PATH=");
	if (!paths__str || !*paths__str)
		px_exit__127(cmd->arr[0], NULL, process);
	paths__arr = ft_split(paths__str, ':');
	if (!paths__arr)
		px_exit("cmd_path", NULL, process);
	paths__get(cmd->arr[0], &cmd->path, paths__arr, process);
	ft_split__free(paths__arr);
}

static void	cmd__arr(t_process *process, char separator)
{
	process->cmd->arr = ft_split(process->cmd_str, separator);
	if (!(process->cmd->arr))
		px_exit("ft_split", NULL, process);
	if (!process->cmd->arr[0])
		px_exit__127("", NULL, NULL);
}

static void	px_cmd__init(t_process *process, char **env)
{
	(process->cmd)->str = process->cmd_str;
	process->cmd->env = env;
	cmd__arr(process, ' ');
	cmd__path(process);
}
// void	get_safe_cmd(t_process *process, char **env)
// {
// 	char	*cmd_str;

// 	cmd_str = ft_strjoin("bash -c ", process->cmd_str);
// 	cmd__free(process->cmd);
// 	process->cmd_str = cmd_str;
// 	px_cmd(process, env);
// 	free(cmd_str);
// }

void	px_cmd(t_process *process, char **env)
{
	t_cmd	cmd;

	process->cmd = &cmd;
	px_cmd__fd(process, FT_FD_OPEN);
	px_cmd__init(process, env);
	execve(cmd.path, cmd.arr, env);
	px_cmd__fd(process, FT_FD_CLOSE);
	px_exit__126(cmd.path, NULL, process);
}

// //find pair of quotes
// static char	(*limits(char *str, char separator))[2]
// {
// 	char	*limits[2];

// 	limits[0] = ft_strchr(str, separator);
// 	if (limits[0]  && limits[0][1])
// 		limits[1] = ft_strchr(limits[0] + 1, separator);
// 	if (!limits[1])
// 		return (NULL);
// 	return (limits);
// }

// static int ft_str__count(char *str, char separator)
// {
// 	int 	i;
// 	char	*ptr;

// 	i = -1;
// 	ptr = str;
// 	while (ptr && *ptr && ++i > -1)
// 		ptr = ft_strchr(ptr, separator);
// 	return (i);
// }

// static void find_chunks(t_process *process, char separator)
// {
// 	char cmd__arr;
// 	int i;
	
// 	i = ft_str__count(process->cmd_str, separator);
// 	if (i % 2)
// 		px_exit("cmd__arr", NULL, process);
// 	if (i)
// 		cmd__arr = ft_split(process->cmd_str, separator);
// }
