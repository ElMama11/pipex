/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generals_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:22:58 by mverger           #+#    #+#             */
/*   Updated: 2022/04/09 20:15:18 by mverger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	check_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char const *set)
{
	char	*output_str;
	int		i;
	int		end;
	int		start;

	i = 0;
	start = 0;
	output_str = NULL;
	if (s1 == NULL)
		return (NULL);
	while (s1[start] && check_set(s1[start], set) == 1)
		start++;
	end = start;
	while (s1[end])
		end++;
	while (end > start && check_set(s1[end - 1], set) == 1)
		end--;
	output_str = (char *)malloc((end - start + 1) * sizeof(char));
	if (output_str == NULL)
		return (NULL);
	while (start != end)
		output_str[i++] = s1[start++];
	output_str[i] = '\0';
	free(s1);
	return (output_str);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_path_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str_malloc;

	str_malloc = NULL;
	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	str_malloc = (char *)malloc((i + j + 2) * sizeof(char));
	if (str_malloc == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		str_malloc[i++] = s1[j++];
	str_malloc[i++] = '/';
	j = 0;
	while (s2[j])
		str_malloc[i++] = s2[j++];
	str_malloc[i] = '\0';
	return (str_malloc);
}

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	int				i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while ((str1[i] != '\0' || str2[i] != '\0') && i < n)
	{
		if (str1[i] != str2[i])
			return ((str1[i] - str2[i]));
		i++;
	}
	return (0);
}
