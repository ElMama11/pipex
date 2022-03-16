/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_infile_access.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 19:54:16 by mverger           #+#    #+#             */
/*   Updated: 2022/03/14 17:10:27 by mverger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	test_infile_access(t_global *global)
{
	if (access(global->infile, R_OK) == 0)
		return (0);
	else
	{
		return (-1);
	}	
}
