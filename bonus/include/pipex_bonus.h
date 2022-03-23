/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:47:23 by mverger           #+#    #+#             */
/*   Updated: 2022/03/23 20:36:55 by mverger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <fcntl.h>

// ft_get_next_line
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

/* STRUCTS */
typedef struct s_global {
	char	**path;
	int		infile_fd;
	int		outfile_fd;
	char	**envv;
}				t_global;

/* cmd_process_bonus.c */
void	exec_cmd(t_global *global, char *cmd);

/* ft_split_bonus.c */
char	**ft_split(char const *s, char c);

/* generals_utils_bonus.c */
static int	check_set(char c, char const *set);
char		*ft_strtrim(char const *s1, char const *set);
int			ft_strlen(const char *s);
char		*ft_path_strjoin(char const *s1, char const *s2);
int			ft_strncmp(const char *s1, const char *s2, int n);

/* get_next_line */
char	*ft_get_next_line(int fd);
char	*ft_strjoin(char const *s1, char const *s2);

/* get_next_line_utils_bonus.c */
char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);

/* here_doc_bonus.c */

void	ft_putstr_fd(char *s, int fd);
void	handle_read_hd(char *argv, int fd[2]);
void	handle_here_doc(char *argv);

/* init_struct_bonus.c */
void	init_struct(t_global *global, char **av, char **env);

/* test_infile_access_bonus.c */
int		test_infile_access(t_global *global);

/* memory_bonus.c */
void	error_exit(char *str);
void	free_all(t_global *global);
void	ft_free_tab(char **tab);


#endif