#include "include/pipex.h"

int	main(int ac, char **av, char **env)
{
	pid_t           pid;
	int           status;
	int	pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
    {
      close(pipefd[0]);
      write(pipefd[1], av[1], strlen(av[1]));
      close(pipefd[1]);
      return 1;
    }
else
    {
      char          buffer[1024];
      int           ret;

      close(pipefd[1]);
      while ((ret = read(pipefd[0], buffer, 1023)))
        {
          buffer[ret] = 0;
          printf("%s\n", buffer);
        }
      close(pipefd[0]);
    }
	
	
	return (0);
}

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