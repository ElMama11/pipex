/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 19:14:16 by mverger           #+#    #+#             */
/*   Updated: 2022/03/19 14:52:42 by mverger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_cmd(t_global *global, int cmd)
{
	char	*cmd_path;
	int		i;

	i = 0;
	if (cmd == 1)
	{
		while (global->path[i])
		{
			cmd_path = ft_sstrjoin(global->path[i], global->cmd1[0]);
			execve(cmd_path, global->cmd1, global->envv);
			free(cmd_path);
			i++;
		}
	}
	else if (cmd == 2)
	{
		while (global->path[i])
		{
			cmd_path = ft_sstrjoin(global->path[i], global->cmd2[0]);
			execve(cmd_path, global->cmd2, global->envv);
			free(cmd_path);
			i++;
		}
	}
	write(2, "command not found\n", 18);
	exit(EXIT_FAILURE);
}

void	cmd1_process(t_global *global, int *pipefd)
{
	dup2(global->infile_fd, STDIN_FILENO);
	if (global->infile_fd == -1)
	{
		perror("redirection of stdin into infile failed: ");
		free_all(global);
	}
	dup2(pipefd[1], STDOUT_FILENO);
	if (pipefd[1] == -1)
	{
		perror("redirection of stdout into pipe failed: ");
		free_all(global);
	}
	close(pipefd[0]);
	close(global->infile_fd);
	exec_cmd(global, 1);
}

void	cmd2_process(t_global *global, int *pipefd)
{
	int		i;
	char	*cmd_path;
	
	i = 0;
	dup2(global->outfile_fd, STDOUT_FILENO);
	if (global->outfile_fd == -1)
	{
		perror("redirection of stdout into outfile failed: ");
		free_all(global);
	}
	dup2(pipefd[0], STDIN_FILENO);
	if (pipefd[0] == -1)
	{
		perror("redirection of stdin into pipe failed: ");
		free_all(global);
	}
	close(pipefd[1]);
	close(global->outfile_fd);
	exec_cmd(global, 2);
}
