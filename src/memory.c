/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 18:28:20 by mverger           #+#    #+#             */
/*   Updated: 2022/03/13 18:36:17 by mverger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void free_all(t_global *global)
{
	ft_free_tab(global->path);
	ft_free_tab(global->cmd1);
	ft_free_tab(global->cmd2);
	//exit(0);
}
