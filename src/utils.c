/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 21:30:29 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/18 22:43:20 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/libft/libft.h"

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
	{
		free(strs[i]);
		strs[i] = NULL;
	}
	if (strs)
		free(strs);
	strs = NULL;
	return ;
}

void	ft_free(void *content)
{
	if (content)
		free(content);
	content = NULL;
}
