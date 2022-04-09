/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 15:19:06 by mverger           #+#    #+#             */
/*   Updated: 2022/04/09 20:15:24 by mverger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (s == NULL)
		return ;
	i = 0;
	while (s[i])
		write(fd, &s[i++], 1);
}

void	handle_read_hd(char *argv, int pipe_fd[2])
{
	char	*line;
	char	*limiter;

	close(pipe_fd[0]);
	limiter = ft_strjoin(argv, "\n");
	line = ft_get_next_line(STDIN_FILENO);
	while (line)
	{
		if (!ft_strncmp(line, limiter, ft_strlen(limiter) + 1))
		{
			close(1);
			free(line);
			free(limiter);
			exit(EXIT_SUCCESS);
		}
		ft_putstr_fd(line, pipe_fd[1]);
		free(line);
		line = ft_get_next_line(STDIN_FILENO);
	}
	close(1);
	free(line);
	free(limiter);
}

void	handle_here_doc(t_global *global, char *argv)
{
	int		pipe_fd[2];
	pid_t	child;

	if (pipe(pipe_fd) == -1)
		error_exit(global, "pipe");
	child = fork();
	if (child < 0)
		error_exit(global, "fork");
	if (child > 0)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		waitpid(child, NULL, 0);
	}
	else
		handle_read_hd(argv, pipe_fd);
}
