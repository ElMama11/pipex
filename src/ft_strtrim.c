/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:17:46 by mverger           #+#    #+#             */
/*   Updated: 2022/03/07 17:08:23 by mverger          ###   ########.fr       */
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

char	*ft_strtrim(char const *s1, char const *set)
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
	return (output_str);
}