/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:55:17 by mverger           #+#    #+#             */
/*   Updated: 2022/03/21 18:57:54 by mverger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	secure_open(char *file, int flag)
{
	int	fd;

	fd = open(file, flag, 0644);
	if (fd == -1)
		error_exit(file);
	return (fd);
}

void	pipex(t_global *global)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (pipe(fd) == -1)
		error_exit("pipe");
	pid = fork();
	if (pid < 0)
		error_exit("fork");
	if (pid > 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		waitpid(pid, &status, 0);
		if (WEXITSTATUS(status) == EXIT_FAILURE)
			exit(EXIT_FAILURE);
	}
	else
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		exec_cmd(global);
	}
}

int	main(int ac, char **av, char **env)
{
	t_global global;

	int	i;
	init_struct(&global, av, env);
	if ((ac >= 5 && ft_strncmp(av[1], "here_doc", 9)) || ac >= 6)
	{
		if (!ft_strncmp(av[1], "here_doc", 9))
		{
			handle_here_doc(av[2]);
			global.outfile_fd = secure_open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND);
			i = 2;
		}
		else
		{
			global.infile_fd = secure_open(av[1], O_RDONLY);
			global.outfile_fd = secure_open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC);
			dup2(global.infile_fd, STDIN_FILENO);
			i = 1;
		}
		global.cmd = ft_split(av[i + 1], ' ');
		while (++i < ac - 2)
			pipex(&global); //incrementer commande
		dup2(global.outfile_fd, STDOUT_FILENO);
		exec_cmd(&global);
	}
	ft_putstr_fd("Error: invalid arguments\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}
