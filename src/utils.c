/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 21:30:29 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/21 00:08:30 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include "../libs/libft/libft.h"
#include "../include/libft_exp.h"
#include "../include/px_exit.h"

char const	*ft_str__find(char **env, char *key)
{
	int	len;
	int	i;

	i = -1;
	len = ft_strlen(key);
	while (env[++i])
		if (!ft_strncmp(env[i], key, len))
			return ((char const *)(env[i] + len));
	return (NULL);
}

void	ft_split__free(char **strs)
{
	int	i;

	i = -1;
	while (strs && strs[++i])
		ft_free(strs[i]);
	if (strs)
		ft_free(strs);
	return ;
}

void	is_dir(t_cmd *cmd)
{
	int			fd;

	fd = open(cmd->arr[0], O_WRONLY);
	if (fd == -1 && errno == EISDIR)
		px_exit__generic(cmd->arr[0], cmd, FREE_CMD, PX_EXIT_126);
	else if (fd != -1)
		close(fd);
	return ;
}

char	*is_path(t_cmd *cmd)
{
	if (ft_strchr(cmd->arr[0], '/'))
	{
		is_dir(cmd);
		cmd->path = ft_strdup(cmd->arr[0]);
		if (!cmd->path)
			px_exit__generic(__func__, cmd, FREE_CMD, PX_EXIT_FAILURE);
	}
	return (cmd->path);
}

void	ft_free(void *content)
{
	if (content)
		free(content);
	content = NULL;
}
