// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   main.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/05/29 10:11:10 by mmirzaie          #+#    #+#             */
// /*   Updated: 2023/09/01 11:17:01 by mehdimirzai      ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

#include "pipex.h"

void	pipex(char *cmd, char **env, char *from)
{
	ft_putstr_fd(from, 2);
	write(2, "\n", 1);
	char	*paths;
	char	*command_path;
	char	**splitted_paths;
	char	**cmd_splitted;
	// int		error_check;

	paths = get_paths(env);
	splitted_paths = ft_split(paths, ':');
	cmd_splitted = ft_split(cmd, ' ');
	command_path = cmd_path(splitted_paths, cmd_splitted[0]);
	if (execve(command_path, cmd_splitted, env) == -1)
		exit(EXIT_FAILURE);
}

// void	child(char *filename, char *cmd, char **env, int fds[])
// {
// 	int infile;

// 	infile = open(filename, O_RDONLY);
// 	dup2(infile, STDIN_FILENO);
// 	dup2(fds[1], STDOUT_FILENO);
// 	close(infile);
// 	close(fds[1]);
// 	close(fds[0]);
// 	pipex(cmd, env, "child");
// }

// void second_child(char *cmd, int fds[], char **env)
// {
// 	// ft_putnbr_fd(getpid(), 2);
// 	// close(fds[1]);
// 	// if (dup2(fds[READ], STDIN_FILENO) == -1)
// 	// {
// 	// 	perror("your gay\n");
// 	// 	exit(EXIT_FAILURE);
// 	// }
// 	// dup2(fds[1], STDOUT_FILENO);
// 	// close(fds[1]);
// 	// close(fds[0]);
// 	(void)fds;
// 	pipex(cmd, env, "second child");
// }

// int main(int ac, char **av, char **env)
// {
// 	int	fds[2];
// 	int fds2[2];
// 	int	pid;
// 	int	outfd;
// 	int	i = 3;

// 	pipe(fds);
// 	pipe(fds2);
// 	pid = fork();
// 	if (pid == 0)
// 		child(av[1], av[2], env, fds);
// 	wait(NULL);
// 	while (i < (ac - 2))
// 	{
// 		pid = fork();
// 		if (pid == -1)
// 			exit(EXIT_FAILURE);
// 		if (pid == 0){
// 			if (i % 2 == 0){
// 				close(fds2[1]);
				
// 				dup2(fds2[1], STDOUT_FILENO);
// 				dup2(fds[READ], STDIN_FILENO);
				
// 				close(fds[0]);
// 				close(fds2[0]);
// 			}
// 			else{
// 				close(fds[0]);
// 				dup2(fds2[READ], STDIN_FILENO);

// 				close(fds2[1]);
// 				close(fds2[0]);
// 			}
// 			second_child(av[i], fds, env);
// 		}

// 		// if (pid == 0){
// 		// 	if (i % 2 == 0){
// 		// 		close(fds2[1]);
				
// 		// 		dup2(fds2[1], STDOUT_FILENO);
// 		// 		dup2(fds[READ], STDIN_FILENO);
				
// 		// 		close(fds[0]);
// 		// 		close(fds2[0]);
				
				
// 		// 		close(fds[1]);
// 		// 	}
// 		// 	else{

// 		// 		close(fds[1]);
// 		// 		// dup2(fds[1], STDOUT_FILENO);
// 		// 		dup2(fds2[READ], STDIN_FILENO);

// 		// 		close(fds2[1]);

// 		// 		close(fds2[0]);
// 		// 		close(fds[0]);
// 		// 	}
// 		// 	second_child(av[i], fds, env);
// 		// }
// 		wait(NULL);
// 		i++;
// 	}
// 	close(fds[1]);
// 	while(wait(NULL) > 0);
// 	outfd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
// 	if (outfd == -1)
// 		exit(EXIT_FAILURE);
// 	dup2(fds[0], STDIN_FILENO);
// 	dup2(outfd, STDOUT_FILENO);
	
	
// 	close(fds[0]);
// 	close(outfd);



// 	pipex(av[ac - 2], env, "main");
// 	return (0);
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int ac, char **av, char **env) {
    int process_num = ac - 5;
	
	int pids[process_num];
    int pipes[process_num + 1][2];
    int i;

	// openning pipes;
    for (i = 0; i < process_num + 1; i++) {
        if (pipe(pipes[i]) == -1) {
            printf("Error with creating pipe\n");
            return 1;
        }
    }


	/*
		if there are more than one pipe
		bellow will run, it closes any in streams that
		isn't i's stream, and closes any out stream that
		isn't (i+1)'s stream.
	*/
    for (i = 0; i < process_num; i++) {
        pids[i] = fork();
        if (pids[i] == -1) {
            printf("Error with creating process\n");
            return 2;
        }
        if (pids[i] == 0) {
            // Child process
            int j;
            for (j = 0; j < process_num + 1; j++) {
                if (i != j) {
                    close(pipes[j][0]);
                }
                if (i + 1 != j) {
                    close(pipes[j][1]);
                }
            }
			dup2(pipes[i][0], STDIN_FILENO);
			dup2(pipes[i + 1][1], STDOUT_FILENO);
            close(pipes[i][0]);
            close(pipes[i + 1][1]);
			pipex(av[i + 3], env, "middle child");
        }
    }

    // Main process
    int j;
    for (j = 0; j < process_num + 1; j++) {
        if (j != process_num) {
            close(pipes[j][0]);
        }
        if (j != 0) {
            close(pipes[j][1]);
        }
    }

	if (fork() == 0){
		close(pipes[process_num][0]);
		int file = open(av[1], O_RDONLY);

		dup2(file, STDIN_FILENO);
		dup2(pipes[0][1], STDOUT_FILENO);


		close(pipes[0][1]);
		close(file);
		pipex(av[2], env, "child\n");
	}
	close(pipes[0][1]);

	int file = open(av[ac - 1], O_WRONLY);
	dup2(file, STDOUT_FILENO);
	dup2(pipes[process_num][0], STDIN_FILENO);
	
	
	close(file);
	close(pipes[process_num][0]);
    close(pipes[0][1]);
    close(pipes[process_num][0]);

	pipex(av[ac - 2], env, "parrant");

	// this statement makes sure that all subprocess have finished.
    for (i = 0; i < process_num; i++) {
        wait(NULL);
    }
    return 0;
}
