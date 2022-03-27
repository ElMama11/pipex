/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:55:17 by mverger           #+#    #+#             */
/*   Updated: 2022/03/27 21:17:56 by mverger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	secure_open(char *file, int flag, t_global *global)
{
	int	fd;

	fd = open(file, flag, 0644);
	if (fd == -1)
		error_exit(global, file);
	return (fd);
}

static int	open_iofiles(t_global *global, char **av, int ac)
{
	int	i;

	i = 1;
	global->infile_fd = secure_open(av[1], O_RDONLY, global);
	global->outfile_fd = secure_open(av[ac - 1],
			O_WRONLY | O_CREAT | O_TRUNC, global);
	dup2(global->infile_fd, STDIN_FILENO);
	return (i);
}

static void	pipex(t_global *global, char *cmd)
{
	int		fd[2];
	pid_t	child;
	int		status;

	if (pipe(fd) == -1)
		error_exit(global, "pipe");
	child = fork();
	if (child == -1)
		error_exit(global, "fork");
	if (child > 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		waitpid(child, &status, 0);
		if (WEXITSTATUS(status) == EXIT_FAILURE)
			exit(EXIT_FAILURE);
	}
	else
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		exec_cmd(global, cmd);
	}
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
			global.outfile_fd
				= secure_open(av[ac - 1],
					O_WRONLY | O_CREAT | O_APPEND, &global);
			i = 2;
		}
		else
			i = open_iofiles(&global, av, ac);
		while (++i < ac - 2)
			pipex(&global, av[i]);
		dup2(global.outfile_fd, STDOUT_FILENO);
		exec_cmd(&global, av[i]);
	}
	write(2, "Error : numbers of args invalid\n", 32);
	ft_free_tab(global.path);
	return (EXIT_FAILURE);
}
