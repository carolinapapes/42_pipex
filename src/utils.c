/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 21:30:29 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/20 01:16:54 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/libft/libft.h"
#include "../include/pipex.h"
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include "../include/px_exit.h"
#include <stdio.h>

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

void	ft_free(void *content)
{
	if (content)
		free(content);
	content = NULL;
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

void	is_dir(char *name)
{
	int			fd;

	fd = open(name, O_WRONLY);
    if (fd == -1 && errno == EISDIR)
            px_exit(name, NULL);
    else if (fd != -1)
        close(fd);
    return ;
}

char	*is_path(char *name, char **path)
{
	if (ft_strchr(name, '/'))
	{
		is_dir(name);
		*path = ft_strdup(name);
		if (!*path)
			px_exit("paths__get ft_strdup failed", NULL);
	}
	return (*path);
}
