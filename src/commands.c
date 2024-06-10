/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 23:18:11 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/09 09:56:06 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/libft/libft.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "pipex.h"

char	*find_path(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (envp[i] + 5);
	return (NULL);
}

int	is_path_valid(char *path, char *command, char **path_command)
{
	char	*path_command_tmp;

	path_command_tmp = ft_strjoin(path, "/");
	if (!path_command_tmp)
		return (0);
	*path_command = ft_strjoin(path_command_tmp, command);
	free(path_command_tmp);
	if (!*path_command)
		return (0);
	return (!access(*path_command, R_OK));
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

char	*command_path(char *command, char **envp)
{
	char	**path_arr;
	char	*path_command;
	int		i;

	path_arr = ft_split((char *const)find_path(envp), ':');
	if (!path_arr)
		return (NULL);
	i = -1;
	while (path_arr[++i] != NULL)
	{
		if (is_path_valid(path_arr[i], command, &path_command))
		{
			free(path_arr[i]);
			return (path_command);
		}
	}
	i = 0;
	while (path_arr[++i])
		free(path_arr[i]);
	free(path_arr);
	return (NULL);
}

void	ft_free_split(char **mem_to_free)
{
	int	i;

	i = -1;
	while (mem_to_free[++i])
		free(mem_to_free[i]);
	free(mem_to_free);
	return ;
}

int	cmd_execve(char **command_arr, char **envp)
{
	execve(command_arr[0], command_arr, envp);
	perror_msg(command_arr[0]);
	ft_free_split(command_arr);
	return (127);
}

int cmd_init(t_cmd *cmd, char *command, char **envp)
{
	cmd->str = command;
	cmd->arr = ft_split(command, ' ');
	if (!(cmd->arr))
		return (127);
	cmd->path = command_path(cmd->arr[0], envp);
	if (cmd->path == NULL)
	{
		ft_free_split(cmd->arr);
		return (perror_cmd_msg(command), 127);
	}
	cmd->env = envp;
	return (0);
}

int		command_call(char *command, char **envp)
{
	t_cmd	cmd;
	int		err;

	if (cmd_init(&cmd, command, envp))
		exit (127);
	err = execve(cmd.path, cmd.arr, envp);
	if (err)
	{
		if (err == -1)
			return (perror_cmd_is_dir(command), 126);
		return (perror_msg(command), 127);
	}
	perror_msg(command);
	ft_free_split(cmd.arr);
	exit (127);
}

// int	command_exec(char *command, char **envp)
// {
// 	char	**cmd_arr;
// 	char	*path;

// 	cmd_arr = ft_split(command, ' ');
// 	if (!cmd_arr)
// 		return (127);
// 	path = command_path(cmd_arr[0], envp);
// 	printf("path: %s\n", path);
// 	if (path == NULL)
// 		return (perror_cmd_msg(command), 127);
// 	printf("accces: %d\n", access(path, F_OK));
// 	if (access(path, F_OK))
// 		return (perror_cmd_is_dir(command), 126);
// 	execve(path, cmd_arr, envp);
// 	perror_msg(command);
// 	ft_free_split(cmd_arr);
// 	return (127);
// }
