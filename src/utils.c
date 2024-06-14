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
	while (strs[++i])
    {
		free(strs[i]);
        strs[i] = NULL;
    }
	free(strs);
    strs = NULL;
	return ;
}