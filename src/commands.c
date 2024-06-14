/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 23:18:11 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/14 00:05:36 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/libft/libft.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "pipex.h"

char const	*ft_str__find(char **env, char *KEY)
{
	int	len;

	len = ft_strlen(KEY);
	while (env++)
		if (!ft_strncmp(env[0], KEY, len))
			return ((char const *)(env[0] + len));
	return (NULL);
}

void	ft_split__free(char **strs)
{
	int	i;

	i = -1;
	while (strs[++i])
		free(strs[i]);
	free(strs);
	return ;
}

char	*is_path_valid(char *path, char *command, char **path_command)
{
	char	*path_command_tmp;
	int		is_valid;

	path_command_tmp = ft_strjoin(path, "/");
	if (!path_command_tmp)
		return (NULL);
	*path_command = ft_strjoin(path_command_tmp, command);
	free(path_command_tmp);
	if (!*path_command)
		return (0);
	is_valid = !access(*path_command, R_OK);
	if (!is_valid)
		free(*path_command);
	return (path_command);
}

void	is_command_relative(char *command, char **path_command)
{
	if (ft_strchr(command, '.' == 0))
	{
		*path_command = ft_strdup(command);
		if (!access(*path_command, R_OK))
			return ;
		free(*path_command);
		*path_command = NULL;
	}
}

char	*command_path(char *command, char **env)
{
	int			i;
	char		**path_arr;
	char		*path_command;
	const char	*paths;

	paths = ft_str__find(env, "PATH=");
	path_arr = ft_split(paths, ':');
	if (!path_arr)
		return (NULL);
	i = -1;
	while (path_arr[++i] != NULL)
	{
		if (is_path_valid(path_arr[i], command, &path_command))
		{
			ft_split__free(path_arr);
			return (path_command);
		}
	}
	ft_split__free(path_arr);
	return (NULL);
}

// add split error handling, add path error handling
int	cmd_init(t_cmd *cmd, char *command, char **env)
{
	cmd->str = command;
	cmd->env = env;
	cmd->arr = ft_split(command, ' ');
	if (!(cmd->arr))
		return (127);
	cmd->path = command_path(cmd->arr[0], env);
	if (cmd->path)
		return (0);
	ft_split__free(cmd->arr);
	perror_cmd_msg(command);
	return (127);
}

int	px_cmd(char *command, char **env)
{
	t_cmd	cmd;

	if (cmd_init(&cmd, command, env))
		exit (127);
	execve(cmd.path, cmd.arr, env);
	perror_msg(command);
	ft_split__free(cmd.arr);
	exit (127);
}
