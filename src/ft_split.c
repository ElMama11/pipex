/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 21:45:02 by mverger           #+#    #+#             */
/*   Updated: 2022/03/07 17:06:22 by mverger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_count_word(char const *strtrim, char c)
{
	int	count_word;
	int	i;	

	i = 0;
	count_word = 0;
	while (strtrim[i])
	{
		if ((strtrim[i] == c && strtrim[i + 1] != c && strtrim[i + 1])
			|| (i == 0 && strtrim[i] != c))
			count_word++;
		i++;
	}
	return (count_word);
}

static int	*ft_count_char(char const *strtrim, char c, int count_word)
{
	int	i;
	int	array_index;
	int	*array_nb_char;
	int	char_count;

	i = 0;
	array_index = 0;
	array_nb_char = (int *)malloc(count_word * sizeof(int));
	if (array_nb_char == NULL)
		return (NULL);
	while (strtrim[i])
	{
		char_count = 0;
		while (strtrim[i] && strtrim[i] != c)
		{
			char_count++;
			i++;
		}
		if (char_count)
			array_nb_char[array_index++] = char_count;
		else
			i++;
	}
	return (array_nb_char);
}

static char	**cpy(char const *strtrim, char **output, char c, int count_word)
{
	int	line;
	int	i;
	int	char_count;

	i = 0;
	line = 0;
	while (strtrim[i] && line < count_word)
	{
		char_count = 0;
		while (strtrim[i] && strtrim[i] != c)
			output[line][char_count++] = strtrim[i++];
		if (strtrim[i] == c)
			i++;
		if (char_count)
		{
			output[line++][char_count] = '\0';
			char_count++;
		}
	}
	output[line] = NULL;
	return (output);
}

static char	**ft_free_split(char **output, int count_malloc)
{
	count_malloc -= 1;
	while (count_malloc >= 0)
	{
		free(output[count_malloc--]);
	}
	free(output);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{	
	int			i;
	int			*array_nb_char;
	char		**output;

	if (s == NULL)
		return (NULL);
	output = (char **)malloc((ft_count_word(s, c) + 1) * sizeof(char *));
	if (output == NULL)
		return (NULL);
	array_nb_char = ft_count_char(s, c, ft_count_word(s, c));
	if (array_nb_char == NULL)
		return (NULL);
	i = -1;
	while (++i < ft_count_word(s, c))
	{
		output[i] = (char *)malloc((array_nb_char[i] + 1) * sizeof(char));
		if (output[i] == NULL)
			return (ft_free_split(output, i));
	}
	free(array_nb_char);
	output = cpy(s, output, c, ft_count_word(s, c));
	return (output);
}
