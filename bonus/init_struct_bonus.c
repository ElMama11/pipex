/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:31:14 by mverger           #+#    #+#             */
/*   Updated: 2022/03/27 20:33:09 by mverger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	init_struct(t_global *global, char **env)
{
	global->path = ft_split(env[6], ':');
	global->path[0] = ft_strtrim(global->path[0], "PATH=");
	global->envv = env;
}
