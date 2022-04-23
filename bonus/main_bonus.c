/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:55:17 by mverger           #+#    #+#             */
/*   Updated: 2022/04/23 03:00:28 by mverger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	redir_last_cmd(int *pipefd, t_global *global)
{
	close(pipefd[0]);
	close(pipefd[1]);
	dup2(global->outfile_fd, STDOUT_FILENO);
}

static void	parent_process(int *pipefd)
{
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
}

static void	pipex(t_global *global, char *cmd, int fd_infile, int last_cmd)
{
	pid_t	child;
	int		pipefd[2];

	pipe(pipefd);
	child = fork();
	if (child > 0)
		parent_process(pipefd);
	else
	{
		if (last_cmd == 1)
			redir_last_cmd(pipefd, global);
		else
		{
			close(pipefd[0]);
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
		}
		if (fd_infile == STDIN_FILENO)
			exit(1);
		else
			exec_cmd(global, cmd);
	}
}

static void	first_exec(t_global *global, int ac, char **av)
{
	global->infile_fd = openfile(av[1], INFILE, global);
	global->outfile_fd = openfile(av[ac - 1], OUTFILE, global);
	dup2(global->infile_fd, STDIN_FILENO);
	pipex(global, av[2], global->infile_fd, ac);
}

int	main(int ac, char **av, char **env)
{
	t_global	global;
	int			i;

	i = 2;
	init_struct(&global, env);
	if (ac >= 5)
	{
		if (!ft_strncmp(av[1], "here_doc", 9))
		{
			handle_here_doc(&global, av[2]);
			global.outfile_fd = openfile_heredoc(av[ac - 1], &global);
		}
		else
			first_exec(&global, ac, av);
		dup2(global.outfile_fd, STDOUT_FILENO);
		while (++i < ac - 1)
			pipex(&global, av[i], 1, (ac - 1) - i);
		while (waitpid(-1, NULL, 0) > 0)
			;
	}
	else
		write(2, "Error : numbers of args invalid\n", 32);
	ft_free_tab(global.path);
	return (EXIT_SUCCESS);
}
