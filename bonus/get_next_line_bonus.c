/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:47:52 by mverger           #+#    #+#             */
/*   Updated: 2022/03/19 17:40:32 by mverger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*copy_with_linefeed(char *buffer, char *output, int output_size)
{
	int	i;

	i = 0;
	while (buffer[i] == '\0')
		i++;
	while (buffer[i] != '\n')
	{
		output[output_size] = buffer[i];
		buffer[i] = '\0';
		i++;
		output_size++;
	}
	buffer[i] = '\0';
	output[output_size] = '\n';
	output[output_size + 1] = '\0';
	return (output);
}

char	*copy_without_linefeed(char *buffer, char *output, int temp_count)
{
	int	i;

	i = 0;
	while (buffer[i] == '\0')
		i++;
	while (buffer[i])
	{
		output[temp_count++] = buffer[i];
		buffer[i++] = '\0';
	}
	buffer[i] = '\0';
	output[temp_count] = '\0';
	return (output);
}

char	*get_line(char *buffer, char *output, int read_output,
	char *output_temp)
{
	int	i;
	int	output_size;
	int	temp_count;	

	temp_count = 0;
	i = 0;
	output_size = ft_strlen(output_temp);
	while (buffer[i] != '\n' && i <= BUFFER_SIZE)
		i++;
	output = (char *)malloc(sizeof(char) * (i + 2 + output_size));
	while (output_size != 0 && output_temp[temp_count])
	{
		output[temp_count] = output_temp[temp_count];
		temp_count++;
	}
	free(output_temp);
	i = 0;
	if (ft_islinefeed(buffer))
		return (output = copy_with_linefeed(buffer, output, output_size));
	else if (read_output == 0)
		return (output = copy_without_linefeed(buffer, output, temp_count));
	return (NULL);
}

char	*get_next_line(int fd)
{
	int			read_output;
	static char	buffer[BUFFER_SIZE + 1];
	char		*output;
	char		*output_temp;

	output_temp = NULL;
	output = NULL;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (0);
	if (ft_check_buffer(buffer))
	{
		read_output = read(fd, buffer, BUFFER_SIZE);
		if (read_output == -1 || read_output == 0)
			return (NULL);
	}
	if (ft_islinefeed(buffer))
		return (output = get_line(buffer, output, read_output, output_temp));
	while (!(ft_islinefeed(buffer)))
	{
		output_temp = ft_strjoin(output_temp, buffer);
		read_output = read(fd, buffer, BUFFER_SIZE);
		if (read_output == 0)
			return (output_temp);
	}
	return (output = get_line(buffer, output, read_output, output_temp));
}
