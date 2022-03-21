/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:47:23 by mverger           #+#    #+#             */
/*   Updated: 2022/03/20 15:23:29 by mverger          ###   ########.fr       */
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
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

/* STRUCTS */
typedef struct s_global {
	char	**path;
	char	*infile;
	char	*outfile;
	char	**cmd;
	int		infile_fd;
	int		outfile_fd;
	char	**envv;
}				t_global;

/* generals_utils_bonus.c */
char	**ft_split(char const *s, char c);
char	*ft_strtrim(char const *s1, char const *set);
int		ft_strlen(const char *s);
char	*ft_sstrjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, int n);

/* get_next_line */
char	*get_next_line(int fd);
int		ft_check_buffer(char *buffer);
int		ft_islinefeed(char *buffer);
char	*ft_strjoin(char *output_temp, char *buffer);
char	*copy_without_linefeed(char *buffer, char *output, int temp_count);

/* ft_split_bonus.c */
char	**ft_split(char const *s, char c);

/* init_struct_bonus.c */
void	init_struct(t_global *global, char **av, char **env);

/* cmd_process_bonus.c */
void	exec_cmd(t_global *global);

/* test_infile_access_bonus.c */
int		test_infile_access(t_global *global);

/* memory_bonus.c */
void	error_exit(char *str);
void	free_all(t_global *global);
void	ft_free_tab(char **tab);

/* here_doc_bonus.c */

void	ft_putstr_fd(char *s, int fd);
void	handle_read_hd(char *argv, int fd[2]);
void	handle_here_doc(char *argv);

#endif