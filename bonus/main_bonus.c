/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:55:17 by mverger           #+#    #+#             */
/*   Updated: 2022/04/09 21:14:54 by mverger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	openfile(char *filename, int mode)
{
	if (mode == INFILE)
	{
		if (access(filename, F_OK) == -1)
		{
			write(2, "pipex: ", 7);
			write(2, filename, ft_strlen(filename));
			write(2, ": No such file or directory\n", 28);
			return (STDIN_FILENO);
		}
		return (open(filename, O_RDONLY));
	}
	else
		return (open(filename, O_CREAT | O_WRONLY | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH));
}

static void	pipex(t_global *global, char *cmd, int fd_infile)
{
	pid_t	child;
	int		pipefd[2];

	pipe(pipefd);
	child = fork();
	if (child > 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		waitpid(child, NULL, 0);
	}
	else
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		if (fd_infile == STDIN_FILENO)
			exit(1);
		else
			exec_cmd(global, cmd);
	}
}

static int	first_exec(t_global *global, int ac, char **av)
{
	global->infile_fd = openfile(av[1], INFILE);
	global->outfile_fd = openfile(av[ac - 1], OUTFILE);
	dup2(global->infile_fd, STDIN_FILENO);
	pipex(global, av[2], global->infile_fd);
	return (3);
}

int	main(int ac, char **av, char **env)
{
	t_global	global;
	int			i;

	init_struct(&global, env);
	if (ac >= 5)
	{
		if (!ft_strncmp(av[1], "here_doc", 9))
		{
			handle_here_doc(&global, av[2]);
			global.outfile_fd = openfile(av[ac - 1], OUTFILE);
			i = 4;
		}
		else
			i = first_exec(&global, ac, av);
		dup2(global.outfile_fd, STDOUT_FILENO);
		while (i < ac - 2)
			pipex(&global, av[i++], 1);
		exec_cmd(&global, av[i]);
	}
	write(2, "Error : numbers of args invalid\n", 32);
	ft_free_tab(global.path);
	return (EXIT_FAILURE);
}
