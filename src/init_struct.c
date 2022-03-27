/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:31:14 by mverger           #+#    #+#             */
/*   Updated: 2022/03/26 14:17:22 by mverger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_struct(t_global *global, char **av, char **env)
{
	global->path = ft_split(env[6], ':');
	global->path[0] = ft_strtrim(global->path[0], "PATH=");
	global->infile = av[1];
	global->cmd1 = ft_split(av[2], ' ');
	global->cmd2 = ft_split(av[3], ' ');
	global->outfile = av[4];
	global->envv = env;
	global->infile_fd = open(global->infile, O_RDONLY);
	if (global->infile_fd == -1)
		perror("infile open failed ");
	global->outfile_fd
		= open(global->outfile, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (global->outfile_fd == -1)
		perror("outfile open failed ");
}
