/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:55:17 by mverger           #+#    #+#             */
/*   Updated: 2022/03/07 18:46:49 by mverger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

void init_struct(t_global *global, char **av, char **env)
{
	global->path = ft_split(env[6], ':');
	global->path[0] = ft_strtrim(global->path[0], "PATH=");
	global->infile = av[1];
	global->cmd1 = av[2];
	global->cmd2 = av[3];
	global->outfile = av[4];
}

int	test_access(t_global *global)
{
	
}

int	main(int ac, char **av, char **env)
{
	pid_t	pid;
	int		status;
	int		pipefd[2];
	t_global global;

	init_struct(&global, av, env);
	for (int i = 0; global.path[i]; i++)
		printf("%s\n", global.path[i]);
	printf("%s", global.outfile);
	return (0);
}
