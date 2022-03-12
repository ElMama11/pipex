/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:47:23 by mverger           #+#    #+#             */
/*   Updated: 2022/03/12 19:57:59 by mverger          ###   ########.fr       */
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
# include <fcntl.h>

/* STRUCTS */
typedef struct s_global {
	char	**path;
	char	*infile;
	char	*outfile;
	char	**cmd1;
	char	**cmd2;
	int		infile_fd;
	int		outfile_fd;
	char	**envv;
}				t_global;

/* generals_utils.c */
char	**ft_split(char const *s, char c);
char	*ft_strtrim(char const *s1, char const *set);
int		ft_strlen(const char *s);
char	*ft_sstrjoin(char const *s1, char const *s2);
void	ft_free_tab(char **tab);

/* ft_split.c */
char	**ft_split(char const *s, char c);

/* init_struct.c */
void init_struct(t_global *global, char **av, char **env);

/* cmd_process.c */
void	cmd1_process(t_global *global, int *pipefd);
void	cmd2_process(t_global *global, int *pipefd);
void	exec_cmd(t_global *global, int cmd);

/* test_infile_access.c */
int	test_infile_access(t_global *global);

#endif