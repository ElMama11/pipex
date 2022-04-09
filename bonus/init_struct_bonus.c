/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:31:14 by mverger           #+#    #+#             */
/*   Updated: 2022/03/28 18:31:59 by mverger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	ft_strchr_tab(char **env, char *to_find)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	if (*to_find == 0)
		return (0);
	while (env[i])
	{
		k = 0;
		while (env[i][k])
		{
			j = 0;
			while (env[i][k + j] == to_find[j])
			{
				if (to_find[j + 1] == 0)
					return (i);
				j++;
			}
			k++;
		}
		i++;
	}
	return (0);
}

void	init_struct(t_global *global, char **env)
{
	global->path = ft_split(env[ft_strchr_tab(env, "PATH=")], ':');
	global->path[0] = ft_strtrim(global->path[0], "PATH=");
	global->infile_access = 1;
	global->envv = env;
}
