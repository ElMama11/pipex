/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:47:23 by mverger           #+#    #+#             */
/*   Updated: 2022/04/09 20:16:54 by mverger          ###   ########.fr       */
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

/* ft_get_next_line */
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# define INFILE 0
# define OUTFILE 1

/* STRUCTS */
typedef struct s_global {
	char	**path;
	int		infile_fd;
	int		outfile_fd;
	int		infile_access;
	char	**envv;
}				t_global;

/* cmd_process.c */
void		exec_cmd(t_global *global, char *cmd);

/* ft_split.c */
char		**ft_split(char const *s, char c);

/* generals_utils.c */
char		*ft_strtrim(char *s1, char const *set);
int			ft_strlen(const char *s);
char		*ft_path_strjoin(char const *s1, char const *s2);
int			ft_strncmp(const char *s1, const char *s2, int n);

/* get_next_line */
char		*ft_get_next_line(int fd);
char		*ft_strjoin(char const *s1, char const *s2);

/* get_next_line.c */
char		*ft_strdup(const char *s1);
char		*ft_strchr(const char *s, int c);
char		*ft_substr(char const *s, int start, int len);

/* here_doc.c */

void		ft_putstr_fd(char *s, int fd);
void		handle_read_hd(char *argv, int pipe_fd[2]);
void		handle_here_doc(t_global *global, char *argv);

/* init_struct.c */
void		init_struct(t_global *global, char **env);

/* memory.c */
void		error_exit(t_global *global, char *str);
void		ft_free_tab(char **tab);

#endif