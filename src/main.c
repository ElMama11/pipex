/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:55:17 by mverger           #+#    #+#             */
/*   Updated: 2022/03/12 19:58:38 by mverger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(t_global *global)
{
	pid_t	child;
	int		status;
	int		pipefd[2];
	
	pipe(pipefd);
	child = fork();
	if (child < 0)
		return (perror("Fork: "));
	if (child == 0)
		cmd1_process(global, pipefd);
	else
	{
		waitpid(child, &status, 0);
		cmd2_process(global, pipefd);
	}
	//close les pipe ?
}

int	main(int ac, char **av, char **env)
{
	t_global global;

	init_struct(&global, av, env);
	if (test_infile_access(&global) == -1)
		return (0);
	if (ac != 5)
	{
		write(2, "Error : numbers of args invalid\n", 32);
		return(0);
	}
	pipex(&global);
	return (0);
}
