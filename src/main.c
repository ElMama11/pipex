/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:55:17 by mverger           #+#    #+#             */
/*   Updated: 2022/03/12 18:31:29 by mverger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	infile_access(t_global *global)
{
	if (access(global->infile, R_OK) == 0)
		return (0);
	else
	{
		perror("infile access : ");
		return (-1);
	}	
}

void	cmd1_process(t_global *global, int *pipefd)
{
	int	i;
	char	*cmd_path;

	i = 0;
	dup2(global->infile_fd, STDIN_FILENO);
	if (global->infile_fd == -1)
		perror("redirection of stdin into infile: ");
	dup2(pipefd[1], STDOUT_FILENO);
	if (pipefd[1] == -1)
		perror("redirection of stdout into pipe: ");
	close(pipefd[0]);
	close(global->infile_fd);
	while (global->path[i])
	{
		cmd_path = ft_sstrjoin(global->path[i], global->cmd1[0]);
		execve(cmd_path, global->cmd1, global->envv);
		perror("execve error: ");
		free(cmd_path);
		i++;
	}
}

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
		close(pipefd[0]);
		close(pipefd[1]);
		waitpid(child, &status, 0);
		//ft_cmd2
	}
}

int	main(int ac, char **av, char **env)
{
	t_global global;

	init_struct(&global, av, env);
	if (infile_access(&global) == -1)
		return (0);
	if (ac != 5)
	{
		write(2, "Error : numbers of args invalid\n", 32);
		return(0);
	}
	pipex(&global);
	// for (int i = 0; global.path[i]; i++)
	// 	printf("%s\n", global.path[i]);
	// printf("%s", global.cmd1[0]);
	return (0);
}
