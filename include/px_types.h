/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 22:15:47 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/20 23:44:39 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PX_TYPES_H
# define PX_TYPES_H

# define PROG_NAME "pipex"

# define READ_END 0
# define WRITE_END 1

# define FT_FD_CLOSE 8
# define FT_FD_DUP 4
# define FT_FD_ERROR 2
# define FT_FD_INIT 1
# define FT_FD_OPEN 7

# define PROG_NAME "pipex"

# include "../libs/libft/libft_bonus.h"

typedef struct s_cmd
{
	char	**arr;
	char	**env;
	char	*path;
	char	**possible_paths;
	int		input[2];
	int		output[2];
	char	*str;
}	t_cmd;

typedef struct s_process
{
	int			input[2];
	int			output[2];
	int			pid;
}	t_process;

typedef struct s_program
{
	char		**cmdv;
	char		**env;
	char		*fd_names[2];
	t_list		*list;
}				t_program;

t_process	*content(t_program *program);

#endif