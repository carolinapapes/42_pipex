#include <unistd.h>
#include "../include/pipex.h"
#include "../include/px_fd.h"
#include "../include/px_types.h"
#include "../include/px_program.h"
#include <stdio.h>

t_process	*content(t_list *list)
{
    return ((t_process *)list->content);
}

int	is_child(t_program *program)
{
	return (!(content(program->list)->pid));
}

int	(*get_fd(t_program *program, int fd))[2]
{
	if (fd == FT_FD_INPUT)
		return (&(content(program->list)->input));
	if (fd == FT_FD_OUTPUT)
		return (&(content(program->list)->output));
	return (NULL);
}

int	is_lastcmdv(t_program *program)
{
	return (!(program->cmdv[1]));
}


