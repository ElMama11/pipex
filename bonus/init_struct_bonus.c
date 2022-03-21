/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:31:14 by mverger           #+#    #+#             */
/*   Updated: 2022/03/20 14:37:47 by mverger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void init_struct(t_global *global, char **av, char **env)
{
	global->path = ft_split(env[6], ':'); //free
	global->path[0] = ft_strtrim(global->path[0], "PATH=");
	global->infile = av[1];
	global->outfile = av[4];
	global->envv = env;
}
