/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 15:19:06 by mverger           #+#    #+#             */
/*   Updated: 2022/03/20 15:27:05 by mverger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (s == NULL)
		return ;
	i = 0;
	while (s[i])
		write(fd, &s[i++], 1);
}

/* handle here document read until limiter */
void	handle_read_hd(char *argv, int fd[2])
{
	char	*line;
	char	*limiter;

	limiter = ft_strjoin(argv, "\n");
	close(fd[0]);
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (!ft_strncmp(line, limiter, ft_strlen(limiter) + 1))
		{
			close(1);
			free(line);
			free(limiter);
			exit(EXIT_SUCCESS);
		}
		ft_putstr_fd(line, fd[1]);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	close(1);
	free(line);
	free(limiter);
}

/* handle here document "<<" */
void	handle_here_doc(char *argv)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
		error_exit("pipe");
	pid = fork();
	if (pid < 0)
		error_exit("fork");
	if (pid > 0)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		waitpid(pid, NULL, 0);
	}
	else
	{
		handle_read_hd(argv, pipe_fd);
	}
}