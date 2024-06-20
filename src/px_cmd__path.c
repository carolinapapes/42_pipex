/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_cmd__path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 22:34:31 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/20 22:41:18 by carolinapap      ###   ########.fr       */
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

char	*who(const char *str)
{
	return ((char *)str);
}

static void	path__concat(char *partial_path, t_cmd *cmd)
{
	char	*tmp;

	tmp = ft_strjoin(partial_path, "/");
	if (!tmp)
		px_exit__cmd(who(__func__), cmd);
	cmd->path = ft_strjoin(tmp, cmd->arr[0]);
	free(tmp);
	if (!cmd->path)
		px_exit__cmd(who(__func__), cmd);
}

static void	paths__get(t_cmd *cmd)
{
	int		i;
	char	**paths__arr;

	paths__arr = cmd->possible_paths;
	i = -1;
	path__concat(paths__arr[++i], cmd);
	while (access(cmd->path, X_OK) && paths__arr[++i])
	{
		ft_free(cmd->path);
		path__concat(paths__arr[i], cmd);
	}
	if (paths__arr[i])
		return ;
	px_exit__127(cmd->arr[0], cmd);
}

static void	get_possible_paths(t_cmd *cmd)
{
	const char	*paths__str;

	paths__str = ft_str__find(cmd->env, "PATH=");
	if (!paths__str || !*paths__str)
		px_exit__127(cmd->arr[0], cmd);
	cmd->possible_paths = ft_split(paths__str, ':');
	if (!cmd->possible_paths)
		px_exit__cmd(who(__func__), cmd);
}

void	cmd__path(t_cmd *cmd)
{
	cmd->path = NULL;
	if (is_path(cmd->arr[0], &cmd->path))
		return ;
	get_possible_paths(cmd);
	paths__get(cmd);
}
