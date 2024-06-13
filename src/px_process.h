
#ifndef PX_PROCESS_H

# define PX_PROCESS_H
# include "../libs/libft/libft.h"
# include "pipex.h"
# include "px_types.h"

void	px_process(t_list **list);
void	io_set(t_list *list, char *file[2], int is_last);

#endif