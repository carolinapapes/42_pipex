
#ifndef PROCESS_H

# define PROCESS_H
# include "../libs/libft/libft.h"
# include "pipex.h"

void	*px_process(t_list **list);
void	io_set(t_list *list, char *file[2], int is_last);

#endif