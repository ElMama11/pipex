/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_process_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 19:14:16 by mverger           #+#    #+#             */
/*   Updated: 2022/03/21 18:51:53 by mverger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exec_cmd(t_global *global)
{
	char		*cmd_path;
	char		**args;
	int			i;

	i = 0;
	// if (*args[0] == '/' || *args[0] == '.' || *args[0] == '~')
	// 	cmd_path = args[0];
	while (global->path[i])
	{
		cmd_path = ft_sstrjoin(global->path[i], global->cmd[0]);
		execve(cmd_path, global->cmd, global->envv);
		free(cmd_path);
		i++;
	}
	error_exit(cmd_path);
}
