/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 19:14:16 by mverger           #+#    #+#             */
/*   Updated: 2022/04/09 20:14:47 by mverger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_cmd(t_global *global, char *cmd)
{
	char		*cmd_path;
	char		**args;
	int			i;

	i = 0;
	args = ft_split(cmd, ' ');
	execve(cmd, args, global->envv);
	while (global->path[i])
	{
		cmd_path = ft_path_strjoin(global->path[i], args[0]);
		execve(cmd_path, args, global->envv);
		free(cmd_path);
		i++;
	}
	error_exit(global, cmd_path);
}
