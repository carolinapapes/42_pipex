/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 23:18:11 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/05 22:10:59 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs/libft/libft.h"
#include <stdio.h>
#include <errno.h>

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
	*path_command = ft_strjoin(path, "/");
	*path_command = ft_strjoin(*path_command, command);
	return (!access(*path_command, F_OK | R_OK));
}

char	*command_path(char *command, char **envp)
{
	char	*path;
	char	**path_arr;
	char	*path_command;
	int		i;

	path = find_path(envp);
	path_arr = ft_split((char *const)path, ':');
	i = -1;
	while (path_arr[++i] != NULL)
		if (is_path_valid(path_arr[i], command, &path_command))
			return (path_command);
	return (NULL);
}

int	command_exec(char *command, char **envp)
{
	char *const	*cmd_arr;
	char		*path;
	int			err;

	cmd_arr = ft_split(command, ' ');
	path = command_path(cmd_arr[0], envp);
	err = execve(path, cmd_arr, 0);
	if (err == -1)
		perror("execve: ");
	return (err);
}
