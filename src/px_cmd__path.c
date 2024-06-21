/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_cmd__path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 22:34:31 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/20 23:55:41 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include "../libs/libft/libft.h"
#include "../include/libft_exp.h"
#include "../include/px_types.h"
#include "../include/px_exit.h"

static void	path__concat(char *partial_path, t_cmd *cmd)
{
	char	*tmp;

	tmp = ft_strjoin(partial_path, "/");
	if (!tmp)
		px_exit__generic(who(__func__), cmd, FREE_CMD, PX_EXIT_FAILURE);
	cmd->path = ft_strjoin(tmp, cmd->arr[0]);
	free(tmp);
	if (!cmd->path)
		px_exit__generic(who(__func__), cmd, FREE_CMD, PX_EXIT_FAILURE);
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
	px_exit__generic(cmd->arr[0], cmd, FREE_CMD, PX_EXIT_127);
}

static void	get_possible_paths(t_cmd *cmd)
{
	const char	*paths__str;

	paths__str = ft_str__find(cmd->env, "PATH=");
	if (!paths__str || !*paths__str)
	{
		errno = ENOENT;
		px_exit__generic(cmd->arr[0], cmd, FREE_CMD, PX_EXIT_127__ENOENT);
	}
	cmd->possible_paths = ft_split(paths__str, ':');
	if (!cmd->possible_paths)
		px_exit__generic(who(__func__), cmd, FREE_CMD, PX_EXIT_FAILURE);
}

void	cmd__path(t_cmd *cmd)
{
	cmd->path = NULL;
	if (is_path(cmd))
		return ;
	get_possible_paths(cmd);
	paths__get(cmd);
}
