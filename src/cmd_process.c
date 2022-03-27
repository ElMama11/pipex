/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 19:14:16 by mverger           #+#    #+#             */
/*   Updated: 2022/03/27 20:45:05 by mverger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	sub_exec_cmd1(t_global *global)
{
	int		i;
	char	*cmd_path;

	i = 0;
	while (global->path[i++])
	{
		cmd_path = ft_sstrjoin(global->path[i], global->cmd1[0]);
		execve(cmd_path, global->cmd1, global->envv);
		free(cmd_path);
	}
	write(2, "command not found\n", 18);
	free(cmd_path);
	free_all(global);
	exit(EXIT_FAILURE);
}

static void	sub_exec_cmd2(t_global *global)
{
	int		i;
	char	*cmd_path;

	i = 0;
	while (global->path[i++])
	{
		cmd_path = ft_sstrjoin(global->path[i], global->cmd2[0]);
		execve(cmd_path, global->cmd2, global->envv);
		free(cmd_path);
	}
	write(2, "command not found\n", 18);
	free(cmd_path);
	free_all(global);
	exit(EXIT_FAILURE);
}

void	exec_cmd(t_global *global, int cmd)
{
	int		i;

	i = 0;
	if (cmd == 1)
		sub_exec_cmd1(global);
	else if (cmd == 2)
		sub_exec_cmd2(global);
}

void	cmd1_process(t_global *global, int *pipefd)
{
	dup2(global->infile_fd, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(global->infile_fd);
	exec_cmd(global, 1);
}

void	cmd2_process(t_global *global, int *pipefd)
{
	int		i;

	i = 0;
	dup2(global->outfile_fd, STDOUT_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[1]);
	close(global->outfile_fd);
	exec_cmd(global, 2);
}
