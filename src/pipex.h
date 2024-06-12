/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:37:37 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/12 01:01:23 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# define READ_END 0
# define WRITE_END 1

# define PROG_NAME "pipex"

typedef struct s_cmd
{
	char	*str;
	char	**arr;
	char	**env;
	char	*path;
}	t_cmd;

typedef struct s_pipe
{
	int	pid_in;
	int	pid_out;
	int	signal_in[1];
	int	signal_out[1];
	int	fd_inside[2];
	int	fd_outside[2];
}		t_pipe;

typedef struct s_cmd_new
{
	char	*path;
	char	*str;
	char	**arr;
	char	**env;
}	t_cmd_new;

typedef struct s_process
{
	t_cmd_new	cmd_new;
	int			pid;
	int			input[2];
	int			output[2];
}	t_process;

typedef  struct s_program
{
	int			fd_names[2];
	int			*cmdc;
	char		**cmdv;
	char		**env;
}				t_program;

int		is_parse_valid(int argc, char **argv);
int		pipex(int argc, char **argv, char **env);
int		command_call(char *command, char **env);
void	perror_msg(char *msg);
void	perror_cmd_msg(char *msg);
void	perror_cmd_is_dir(char *msg);
int		process_child(int *fd_input, int *fd_output, char *command, char **env);
void	fd_close(int *fd);
int		pipex_new(int argc, char **argv, char **env);
char	*command_path(char *command, char **env);

#endif