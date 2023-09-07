/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 10:11:10 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/09/07 12:43:00 by mehdimirzai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (file == -1)
		exit(127);
	dup2(file, STDIN_FILENO);
	dup2(pipes[0][1], STDOUT_FILENO);
	close(pipes[0][1]);
	close(file);
	if (args.temp_file_created == true)
		if (unlink(args.av[1]) == -1) // Remove the temporary file
			perror("unlink");
	pipex(args.av[2], args.env);
}

void	parent(const t_args args, int pipes[][2])
{
	int	file;
	int	i;

	close(pipes[0][1]);
	if (args.temp_file_created == true)
		file = open(args.av[args.ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0664);
	else
		file = open(args.av[args.ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (file == -1)
	{
		printf("yours gay!\n");
		exit(127);
	}
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
#include "get_next_line.h"

int open_pipes(t_args args, int pipes[][2])
{
	int	i;

	i = 0;
	while (i < args.process_num + 1)
	{
		if (pipe(pipes[i++]) == -1)
		{
			printf("Error with creating pipe\n");
			return (1);
		}
	}
	return (0);
}

int	create_middle_process(t_args args, int pipes[][2])
{
	int	i;

	i = 0;
	while (i < args.process_num)
	{
		args.pids[i] = fork();
		if (args.pids[i] == -1)
		{
			printf("Error with creating process\n");
			return (2);
		}
		if (args.pids[i] == 0)
			middle_child(args, pipes, i);
		i++;
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	int		process_num = ac - 5;
	int				pids[MAX_PROCESS_NUM];
	int				pipes[MAX_PROCESS_NUM][2];
	t_args	args = {av, ac, process_num, env, pids, false};

	if (ac < 3)
		return (127);

	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		char* template = "/tmp/mytempfileXXXXXX";
		int fd;
		
		// Create a unique file name
		char *filename = strdup(template);

		fd = open(filename, O_CREAT | O_RDWR | O_EXCL, S_IRUSR | S_IWUSR);
		if (fd == -1)
			exit(127);
		args.temp_file_created = true;
		int	limiter_len = ft_strlen(av[2]);
		char *lines;
		lines = get_next_line(STDIN_FILENO);
		while (ft_strncmp(lines, av[2], limiter_len) != 0)
		{
			ft_putstr_fd(lines, fd);
			free(lines);
			lines = get_next_line(STDIN_FILENO);
		}
		av[1] = filename;
		av[2] = av[3];
		av[3] = av[4];
		av[4] = av[5];
		args.ac = 5;
		args.process_num = ac - 5;
		if (open_pipes(args, pipes) == 1)
			return (1);
		if (create_middle_process(args, pipes) == 2)
			return (2);
		master(args, pipes);
		// close(fd);
		// free(filename);
	}

		
	if (ac == 4)
	{
		int fd[2];
		pipe(fd);
		if (fork() == 0){
			close(fd[0]);
			int file = open(av[1], O_RDONLY);
			if (file == -1)
				exit(127);
			dup2(file, STDIN_FILENO);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			close(file);
			pipex(av[2], env);
		}
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		int file = open(av[3], O_WRONLY | O_CREAT | O_TRUNC, 0664);
		if (file == -1)
			exit(127);
		dup2(file, STDOUT_FILENO);
		close(file);
		close(fd[0]);
		pipex(av[3], env);
	}
	
	if (open_pipes(args, pipes) == 1)
		return (1);
	if (create_middle_process(args, pipes) == 2)
		return (2);
	master(args, pipes);
	return (0);
}