/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 20:19:49 by mverger           #+#    #+#             */
/*   Updated: 2022/03/19 17:40:18 by mverger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_check_buffer(char *buffer)
{
	int	i;

	i = 0;
	while (i <= BUFFER_SIZE)
	{
		if (buffer[i] != '\0')
			return (0);
		i++;
	}
	return (1);
}

int	ft_islinefeed(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i] == '\0')
		i++;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *output_temp, char *buffer)
{
	int		i;
	int		j;
	char	*output;

	i = 0;
	j = 0;
	if (output_temp == NULL && buffer == NULL)
		return (NULL);
	output = (char *)malloc((ft_strlen(output_temp) + ft_strlen(buffer) + 1)
			* sizeof(char));
	if (output == NULL)
		return (NULL);
	while (output_temp != NULL && output_temp[i])
	{
		output[i] = output_temp[i];
		i++;
	}
	free(output_temp);
	return (output = copy_without_linefeed(buffer, output, i));
}
