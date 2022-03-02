/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:55:17 by mverger           #+#    #+#             */
/*   Updated: 2022/03/01 17:43:49 by mverger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

int	main(int ac, char **av, char **env)
{
	pid_t           pid;
  int           status;

	pid = fork();
  if (ac > 1)
    {
      if (pid == -1)
        {
          perror("fork");
          return 1;
        }
      /* Si pid == 0, alors on est dans le process fils. */
      else if (pid == 0)
        {
          if (execve(av[1], av + 1, env) == -1)
            perror("execve");
          return 1; /* On termine le fils même si execve fail parce qu'on veut voir que le pid du pere*/
        }
      /* Sinon, dans le pere. */
      else
        wait(&status); /* Oui, il faudrait vérifier la valeur de retour... */
    }

  printf("My pid is: %d\n", getpid());

  return 0;

// 	int pipefd[2];
//   int pid;

//   char *ll_args[] = {"ls", "-l", NULL};
//   char *wc_args[] = {"wc", "-l", NULL};

//   // make a pipe (fds go in pipefd[0] and pipefd[1])

//   pipe(pipefd);
//   pid = fork();
//   if (pid == 0)
//     {
//       // child gets here and handles "wc -l"
//       // replace standard input with input part of pipe
//       dup2(pipefd[0], 0);

//       // close unused hald of pipe
//       close(pipefd[1]);

//       // execute wc -l
//       execvp("wc", wc_args);
//     }
//   else
//     {
//       // parent gets here and handles "ls -l"
//       // replace standard output with output part of pipe
//       dup2(pipefd[1], 1);

//       // close unused unput half of pipe
//       close(pipefd[0]);

//       // execute ls -l
//       execvp("ls", ll_args);
//     }

//   return 0;
}