/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:47:23 by mverger           #+#    #+#             */
/*   Updated: 2022/03/07 17:56:56 by mverger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>

/* STRUCTS */
typedef struct s_global {
	char	**path;
	char	*infile;
	char	*outfile;
	char	*cmd1;
	char	*cmd2;
}		t_global;

/* ft_split.c */
char	**ft_split(char const *s, char c);

/* ft_strtrim */
char	*ft_strtrim(char const *s1, char const *set);

#endif