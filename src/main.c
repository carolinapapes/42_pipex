/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:37:46 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/12 21:51:02 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../libs/libft/libft.h"
#include <stdio.h>

void	program_cmds_structure(t_program **program, char **argv, int argc)
{
	int	i;

	(*program)->cmdv = malloc(sizeof(char *) * (*program)->cmdc);
	if (!(*program)->cmdv)
	{
		ft_putstr_fd("Pipex: malloc error.\n", 1);
		exit(1);
	}
	i = 1;
	while (++i < argc - 1)
		(*program)->cmdv[i - 2] = argv[i];
	(*program)->cmdv[i - 2] = NULL;
	return ;
}

void	separate_arguments(t_program **program, char **argv, int argc, char **env)
{
	(*program)->fd_names[READ_END] = argv[1];
	(*program)->fd_names[WRITE_END] = argv[argc - 1];
	(*program)->cmdc = argc - 3;
	(*program)->env = env;
	program_cmds_structure(program, argv, argc);
	return ;
}

void	init_program_structure(t_program **program, int argc, char **argv, char **env)
{
	*program = malloc(sizeof(t_program));
	if (!(program))
	{
		ft_putstr_fd("Pipex: malloc error.\n", 1);
		exit(1);
	}
	separate_arguments(program, argv, argc, env);
}

int	main(int argc, char **argv, char **env)
{
	t_program	*program;

	if (!is_parse_valid(argc, argv))
		return (1);
	init_program_structure(&program, argc, argv, env);
	return (pipex_new(program));
}
