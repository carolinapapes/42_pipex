#include "../libs/libft/libft.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "../include/pipex.h"
#include "../include/px_types.h"
#include "../include/px_process.h"
#include "../include/px_exit.h"

static void	path__concat(char *name, char *partial_path, char **path, t_cmd *cmd)
{
	char	*tmp;

	tmp = ft_strjoin(partial_path, "/");
	if (!tmp)
		px_exit__cmd("path__concat ft_strjoin failed", cmd);
	*path = ft_strjoin(tmp, name);
	free(tmp);
	if (!*path)
		px_exit__cmd("path__concat ft_strjoin failed", cmd);
}

static void	paths__get(t_cmd *cmd)
{
	int			i;
	char	*name = cmd->arr[0];
	char 	**path = &cmd->path;
    char	**paths__arr = cmd->possible_paths;

	i = -1;
	path__concat(name, paths__arr[++i], path, cmd);
	while (access(*path, X_OK) && paths__arr[++i])
	{
		free(*path);
		*path = NULL;
		path__concat(name, paths__arr[i], path, cmd);
	}
	if (paths__arr[i])
		return ;
	px_exit__127(name, cmd);
}

static void get_possible_paths(t_cmd *cmd)
{
    const char	*paths__str;

    paths__str = ft_str__find(cmd->env, "PATH=");
	if (!paths__str || !*paths__str)
		px_exit__127(cmd->arr[0], cmd);
	cmd->possible_paths = ft_split(paths__str, ':');
	if (!cmd->possible_paths)
		px_exit__cmd("cmd_path", cmd);
}

void	cmd__path(t_cmd *cmd)
{
	cmd->path = NULL;
	if (is_path(cmd->arr[0], &cmd->path))
		return ;
	get_possible_paths(cmd);
	paths__get(cmd);
}