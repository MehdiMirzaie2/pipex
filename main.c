/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 10:11:10 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/09/05 16:36:22 by mehdimirzai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include "pipex.h"

void	middle_child(const t_args args, int pipes[][2], int i)
{
	int	j;

	j = 0;
	while (j < args.process_num + 1)
	{
		if (i != j)
			close(pipes[j][0]);
		if (i + 1 != j)
			close(pipes[j][1]);
		j++;
	}
	dup2(pipes[i][0], STDIN_FILENO);
	dup2(pipes[i + 1][1], STDOUT_FILENO);
	close(pipes[i][0]);
	close(pipes[i + 1][1]);
	pipex(args.av[i + 3], args.env);
}

void	child(const t_args args, int pipes[][2])
{
	int	file;

	close(pipes[args.process_num][0]);
	file = open(args.av[1], O_RDONLY);
	dup2(file, STDIN_FILENO);
	dup2(pipes[0][1], STDOUT_FILENO);
	close(pipes[0][1]);
	close(file);
	pipex(args.av[2], args.env);
}

void	parent(const t_args args, int pipes[][2])
{
	int	file;
	int	i;

	close(pipes[0][1]);
	file = open(args.av[args.ac - 1], O_WRONLY);
	dup2(file, STDOUT_FILENO);
	dup2(pipes[args.process_num][0], STDIN_FILENO);
	close(file);
	close(pipes[args.process_num][0]);
	close(pipes[0][1]);
	close(pipes[args.process_num][0]);
	pipex(args.av[args.ac - 2], args.env);
	i = 0;
	while (i++ < args.process_num)
		wait(NULL);
}

void	master(const t_args args, int pipes[][2])
{
	int	j;

	j = 0;
	while (j < args.process_num + 1)
	{
		if (j != args.process_num)
			close(pipes[j][0]);
		if (j != 0)
			close(pipes[j][1]);
		j++;
	}
	if (fork() == 0)
		child(args, pipes);
	parent(args, pipes);
}

#define MAX_PROCESS_NUM 100

int	main(int ac, char **av, char **env)
{
	const int		process_num = ac - 5;
	int				pids[MAX_PROCESS_NUM];
	int				pipes[MAX_PROCESS_NUM][2];
	int				i;
	const t_args	args = {av, ac, process_num, env};

	i = 0;
	while (i < process_num + 1)
	{
		if (pipe(pipes[i++]) == -1)
		{
			printf("Error with creating pipe\n");
			return (1);
		}
	}
	i = 0;
	while (i < process_num)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			printf("Error with creating process\n");
			return (2);
		}
		if (pids[i] == 0)
			middle_child(args, pipes, i);
		i++;
	}
	master(args, pipes);
	return (0);
}
