#ifndef PX_TYPES_H

# define PX_TYPES_H

typedef struct s_process
{
	int			pid;
	int			input[2];
	int			output[2];
}	t_process;

typedef struct s_program
{
	char		*fd_names[2];
	int			cmdc;
	char		**cmdv;
	char		**env;
}				t_program;

#endif