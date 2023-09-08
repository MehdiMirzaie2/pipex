/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 10:11:10 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/09/08 12:43:55 by mehdimirzai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "next_line.h"

void	middle_child(const t_args args, int pipes[][2], int i)
{
	int	j;

	j = 0;
	while (j < *(args.process_num) + 1)
	{
		if (i != j)
			close(pipes[j][0]);
		if (i + 1 != j)
			close(pipes[j][1]);
		j++;
	}
	if ((redirect_input(pipes[i][0], STDIN_FILENO) == -1)
		|| redirect_output(pipes[i + 1][1], STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	pipex(args.av[i + 3], args.env);
}

void	child(const t_args args, int pipes[][2])
{
	int	file;

	close(pipes[*(args.process_num)][0]);
	file = open(args.av[1], O_RDONLY);
	if (file == -1)
		exit(127);
	if ((redirect_input(file, STDIN_FILENO) == -1)
		|| redirect_output(pipes[0][1], STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (args.temp_file_created == true)
		if (unlink(args.av[1]) == -1)
			perror("unlink");
	pipex(args.av[2], args.env);
}

void	parent(const t_args args, int pipes[][2])
{
	int	file;
	int	i;

	close(pipes[0][1]);
	if (args.temp_file_created == true)
		file = open(args.av[*(args.ac) - 1], O_WRONLY | O_CREAT | O_APPEND, 0664);
	else
		file = open(args.av[*(args.ac) - 1], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (file == -1)
		exit(127);
	if ((redirect_input(file, STDOUT_FILENO) == -1)
		|| redirect_output(pipes[*(args.process_num)][0], STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	i = 0;
	while (i++ < *(args.process_num))
		wait(NULL);
	pipex(args.av[*(args.ac) - 2], args.env);
}

void	master(const t_args args, int pipes[][2])
{
	int	j;

	j = 0;
	while (j < *(args.process_num) + 1)
	{
		if (j != *(args.process_num))
			close(pipes[j][0]);
		if (j != 0)
			close(pipes[j][1]);
		j++;
	}
	if (fork() == 0)
		child(args, pipes);
	parent(args, pipes);
}

int	open_pipes(t_args args, int pipes[][2])
{
	int	i;

	i = 0;
	while (i < *(args.process_num) + 1)
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
	while (i < *(args.process_num))
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

void	new_av(t_args args, char *filename)
{
	int	i;

	i = 2;
	args.av[1] = filename;
	while (i < (*(args.ac) - 1))
	{
		args.av[i] = args.av[i + 1];
		i++;
	}
	*args.ac = i;
	*args.process_num = *(args.ac) - 5;
}

int	heredoc(t_args args, int pipes[][2])
{
	const char	*template = "/tmp/mytempfileXXXXXX";
	int			fd;
	char		*filename;
	char		*lines;
	int			limiter_len;

	filename = ft_strdup(template);
	fd = open(filename, O_CREAT | O_RDWR | O_EXCL, S_IRUSR | S_IWUSR);
	if (fd == -1)
		exit(127);
	args.temp_file_created = true;
	limiter_len = ft_strlen(args.av[2]);
	lines = get_next_line(STDIN_FILENO);
	while (ft_strncmp(lines, args.av[2], limiter_len) != 0)
	{
		ft_putstr_fd(lines, fd);
		free(lines);
		lines = get_next_line(STDIN_FILENO);
	}
	new_av(args, filename);
	// args.av[1] = filename;
	// args.av[2] = args.av[3];
	// args.av[3] = args.av[4];
	// args.av[4] = args.av[5];
	// *(args.ac) = 5;
	// *(args.process_num) = *(args.ac) - 5;
	if (open_pipes(args, pipes) == 1 || create_middle_process(args, pipes) == 2)
		return (1);
	master(args, pipes);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	int		pids[MAX_PROCESS_NUM];
	int		pipes[MAX_PROCESS_NUM][2];
	t_args	args;

	args = (t_args){.av = av, .ac = &ac,
		.process_num = &ac - 5,
		.env = env, .pids = pids, .temp_file_created = false};
	if (*env == NULL)
		return (0);
	if (ac < 3)
		return (127);
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
		if (heredoc(args, pipes) != 0)
			exit(EXIT_FAILURE);
	if (open_pipes(args, pipes) == 1)
		return (1);
	if (create_middle_process(args, pipes) == 2)
		return (2);
	master(args, pipes);
	return (0);
}
