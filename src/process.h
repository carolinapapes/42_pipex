
#ifndef PROCESS_H

# define PROCESS_H
# include "../libs/libft/libft.h"
# include "pipex.h"

void	*create_process(t_list **list);
void	io_set(t_list *list, t_process *current, char *file, int position);

#endif