/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 23:18:11 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/20 15:56:00 by carolinapap      ###   ########.fr       */
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

static void	path__concat(char *name, char *partial_path, char **path)
{
	char	*tmp;

	tmp = ft_strjoin(partial_path, "/");
	if (!tmp)
		px_exit("path__concat ft_strjoin failed", NULL, NULL);
	*path = ft_strjoin(tmp, name);
	free(tmp);
	if (!*path)
		px_exit("path__concat ft_strjoin failed", NULL, NULL);
}

static void	paths__get(char *name, char **path, char **paths__arr)
{
	int			i;

	i = -1;
	path__concat(name, paths__arr[++i], path);
	while (access(*path, X_OK) && paths__arr[++i])
	{
		free(*path);
		*path = NULL;
		path__concat(name, paths__arr[i], path);
	}
	if (paths__arr[i])
		return ;
	free(*path);
	*path = NULL;
	px_exit__127(name, NULL, NULL);
}

static void	get__path(t_cmd *cmd)
{
	const char	*paths__str;
	char		**paths__arr;

	cmd->path = NULL;
	if (is_path(cmd->arr[0], &cmd->path))
		return ;
	paths__str = ft_str__find(cmd->env, "PATH=");
	if (!paths__str || !*paths__str)
		px_exit__127(cmd->arr[0], NULL, NULL);
	paths__arr = ft_split(paths__str, ':');
	if (!paths__arr)
		px_exit("cmd_path", NULL, NULL);
	paths__get(cmd->arr[0], &cmd->path, paths__arr);
	ft_split__free(paths__arr);
}

static void	get__arr(t_cmd *cmd, char separator)
{
	cmd->arr = ft_split(cmd->str, separator);
	if (!(cmd->arr))
		px_exit("ft_split", NULL, NULL);
	if (!cmd->arr[0])
		px_exit__127("", NULL, NULL);
}

void	px_cmd__exec(t_cmd *cmd)
{
	px_cmd__fd(cmd, FT_FD_OPEN);
	get__arr(cmd, ' ');
	get__path(cmd);
	execve(cmd->path, cmd->arr, cmd->env);
	px_cmd__fd(cmd, FT_FD_CLOSE);
	px_exit__126(cmd->path, NULL, NULL);
}
