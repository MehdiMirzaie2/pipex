/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 10:11:10 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/05/31 10:41:08 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(char *cmd, char **env)
{
	char	*paths;
	char	*command_path;
	char	**splitted_paths;
	char	**cmd_splitted;
	int		error_check;

	paths = get_paths(env);
	splitted_paths = ft_split(paths, ':');
	cmd_splitted = ft_split(cmd, ' ');
	command_path = cmd_path(splitted_paths, cmd_splitted[0]);
	error_check = execve(command_path, cmd_splitted, env);
	if (error_check == -1)
	{
		perror("execve error");
		exit(0);
	}
}

void	parent_process(char *file_name, char *cmd, int pipe_fd[], char **env)
{
	int	second_file_fd;

	second_file_fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (second_file_fd == -1)
	{
		perror("parent open error");
		exit(EXIT_FAILURE);
	}
	dup2(pipe_fd[0], STDIN_FILENO);
	dup2(second_file_fd, STDOUT_FILENO);
	close(second_file_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	pipex(cmd, env);
}

void	child_process(char *file_name, char *cmd, int pipe_fd[], char **env)
{
	int	first_file_fd;

	first_file_fd = open(file_name, O_RDONLY, 0777);
	if (first_file_fd == -1)
	{
		perror("child open error");
		exit(EXIT_FAILURE);
	}
	close(STDIN_FILENO);
	dup2(first_file_fd, STDIN_FILENO);
	close(first_file_fd);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	pipex(cmd, env);
}

int	main(int ac, char **av, char **env)
{
	int		pid;
	int		pipe_fd[2];

	if (ac != 5)
	{
		perror("ac error");
		exit(EXIT_FAILURE);
	}
	(void) ac;
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe error");
		exit(-1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork error");
		exit(-1);
	}
	if (pid == 0)
		child_process(av[1], av[2], pipe_fd, env);
	parent_process(av[4], av[3], pipe_fd, env);
	return (0);
}
