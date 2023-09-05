/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 12:11:44 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/09/04 11:27:12 by mehdimirzai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	perror("access error");
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
