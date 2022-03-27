/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line_utils_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 19:53:44 by mverger           #+#    #+#             */
/*   Updated: 2022/03/27 21:17:13 by mverger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*str_malloc;

	i = 0;
	while (s1[i])
		i++;
	str_malloc = (char *) malloc((i + 1) * sizeof(char));
	if (str_malloc == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str_malloc[i] = s1[i];
		i++;
	}
	str_malloc[i] = '\0';
	return (str_malloc);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned char	to_find;

	to_find = (unsigned char)c;
	if (to_find == '\0')
	{
		while (to_find != *s)
		{
			s++;
		}
		return ((char *)s);
	}
	while (*s != '\0')
	{
		if (to_find == *s)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

char	*ft_substr(char const *s, int start, int len)
{
	int		i;
	char	*str_malloc;

	str_malloc = NULL;
	if (s == NULL)
		return (NULL);
	i = ft_strlen(s);
	if (start >= i)
		return (ft_strdup("\0"));
	if (len >= i - start)
		str_malloc = (char *)malloc(((i - start) + 1) * sizeof(char));
	else if (len < i - start)
		str_malloc = (char *)malloc((len + 1) * sizeof(char));
	if (str_malloc == NULL)
		return (NULL);
	i = 0;
	while (i < len && i <= ft_strlen(s))
		str_malloc[i++] = s[start++];
	str_malloc[i] = '\0';
	return (str_malloc);
}
