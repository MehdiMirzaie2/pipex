/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 12:11:44 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/09/05 19:59:20 by mehdimirzai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(char *cmd, char **env)
{
	char	*paths;
	char	*command_path;
	char	**splitted_paths;
	char	**cmd_splitted;
	int		pos;

	paths = get_paths(env);
	splitted_paths = ft_split(paths, ':');
	cmd_splitted = ft_split(cmd, ' ');
	pos = ft_strrchrpos(cmd_splitted[0], '/');
	if (pos != 0)
	{
		command_path = cmd_splitted[0];
		cmd_splitted[0] = ft_substr(cmd_splitted[0], pos, ft_strlen(cmd_splitted[0]));
	}
	else
		command_path = cmd_path(splitted_paths, cmd_splitted[0]);
	if (cmd_splitted[1] != NULL)
		if (cmd_splitted[1][0] == '\'')
			cmd_splitted[1] = ft_substr(cmd_splitted[1], 1, ft_strlen(cmd_splitted[1] - 1));
	if (execve(command_path, cmd_splitted, env) == -1)
		exit(EXIT_FAILURE);
}

void	found_error(char *str, int error)
{
	(void)error;
	perror(str);
	exit(EXIT_FAILURE);
}

char	*get_paths(char **env)
{
	int		err_check;
	char	*path;

	while (*env)
	{
		err_check = ft_strncmp(*env, "PATH=", 5);
		if (err_check == 0)
		{
			path = *env + 5;
			return (path);
		}
		++env;
	}
	return (NULL);
}

char	*ft_strcat(char *path, char *cmd)
{
	int		len_path;
	int		len_cmd;
	char	*file_path;
	int		i;
	int		j;

	i = -1;
	j = -1;
	len_path = ft_strlen(path);
	len_cmd = ft_strlen(cmd);
	file_path = malloc(sizeof(char) * (len_cmd + len_path + 2));
	if (file_path == NULL)
		return (NULL);
	while (++i < len_path)
		file_path[i] = path[i];
	file_path[i++] = '/';
	while (++j < len_cmd)
		file_path[i + j] = cmd[j];
	file_path[i + j] = '\0';
	return (file_path);
}

char	*cmd_path(char **splitted_paths, char *cmd)
{
	char	*file_path;
	int		val;

	while (*splitted_paths)
	{
		file_path = ft_strcat(*splitted_paths, cmd);
		val = access(file_path, X_OK);
		if (val == 0)
			return (file_path);
		free(file_path);
		++splitted_paths;
	}
	ft_putstr_fd(cmd, 2);
	perror("command not found");
	exit(127);
}

void	free_split_paths(char **splitted_paths)
{
	char	**temp;

	temp = splitted_paths;
	while (*temp)
	{
		free(*temp);
		++temp;
	}
	free(splitted_paths);
}
