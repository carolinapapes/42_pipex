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

/*
path__concat
	- concat partial path with /
	- concat previous result with command
	- free tmp
	- return
*/
static void	path__concat(char *cmd_name, char *partial_path, char **cmd_path)
{
	char	*tmp;

	tmp = ft_strjoin(partial_path, "/");
	if (!tmp)
		return ;
	*cmd_path = ft_strjoin(tmp, cmd_name);
	free(tmp);
	tmp = NULL;
}

/*
paths__get
	- iterate over paths while path is not valid
		- concat env path with command

*/
static void	paths__get(char *cmd_name, char **cmd_path, char **paths__arr)
{
	int			i;

	i = -1;
	path__concat(cmd_name, "", cmd_path);
	while (access(*cmd_path, R_OK) && paths__arr[++i])
	{
		free(*cmd_path);
		*cmd_path = NULL;
		path__concat(cmd_name, paths__arr[i], cmd_path);
	}
}

// add split error handling, add path error handling
static void	cmd__arr(t_cmd *cmd, char separator)
{
	cmd->arr = ft_split(cmd->str, separator);
	if (!(cmd->arr))
		exit (127);
}

/*
cmd__path
	- get path from env
	- split path
	- get vallid path
	- return or if path is not valid, print error message, clean and exit
*/
// Add split error handling
// add path error handling
// What happens if path doesnt exist?
static void	cmd__path(t_cmd *cmd)
{
	const char	*paths__str;
	char		**paths__arr;

	paths__str = ft_str__find(cmd->env, "PATH=");
	paths__arr = ft_split(paths__str, ':');
	paths__get(cmd->arr[0], &cmd->path, paths__arr);
	ft_split__free(paths__arr);
	if (cmd->path)
		return ;
	// perror_cmd_msg(cmd->arr[0]);
	// ft_split__free(cmd->arr);
}

// add split error handling, add path error handling
static void	px_cmd__init(t_cmd *cmd, char *command, char **env)
{
	cmd->str = command;
	cmd->env = env;
	cmd__arr(cmd, ' ');
	cmd__path(cmd);
}

int	px_cmd(char *command, char **env)
{
	t_cmd	cmd;

	px_cmd__init(&cmd, command, env);
	execve(cmd.path, cmd.arr, env);
	perror_msg(command);
	ft_split__free(cmd.arr);
	exit (127);
}
