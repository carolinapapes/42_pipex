#include "libft.h"

int	is_first_item(t_list *list)
{
	if (!list->next)
		return (1);
	return (0);
}

void	*ft_lst_beforelast(t_list *list)
{
	t_list	*tmp;

	if (!list || !list->next)
		return (NULL);
	tmp = list;
	while (tmp->next && tmp->next->next)
		tmp = tmp->next;
	return (tmp->content);
}