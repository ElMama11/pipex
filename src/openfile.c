/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 16:13:21 by mverger           #+#    #+#             */
/*   Updated: 2022/04/22 17:20:58 by mverger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	check_access_outfile(t_global *global, char *filename)
{
	write(2, "pipex: permission denied: ", 26);
	write(2, filename, ft_strlen(filename));
	write(2, "\n", 1);
	ft_free_tab(global->path);
	exit(EXIT_FAILURE);
}

int	openfile(char *filename, int mode, t_global *global)
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
		else if (access(filename, R_OK) == -1)
		{
			write(2, "pipex: permission denied: ", 26);
			write(2, filename, ft_strlen(filename));
			write(2, "\n", 1);
			return (STDIN_FILENO);
		}
		return (open(filename, O_RDONLY));
	}
	else
	{
		if (access(filename, F_OK) != -1 && access(filename, W_OK) == -1)
			check_access_outfile(global, filename);
		return (open(filename, O_CREAT | O_WRONLY | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH));
	}
}

int	openfile_heredoc(char *filename, t_global *global)
{
	if (access(filename, F_OK) != -1 && access(filename, W_OK) == -1)
			check_access_outfile(global, filename);
		return (open(filename, O_CREAT | O_WRONLY | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH));
}