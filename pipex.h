/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 12:57:21 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/05/30 12:58:13 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include "libft.h"

char	*get_paths(char **env);
char	*ft_strcat(char *path, char *cmd);
char	*cmd_path(char **splitted_paths, char *cmd);
void	free_split_paths(char **splitted_paths);
void	pipex(char *cmd, char **env);
void	parent_process(char *file_name, char *cmd, int pipe_fd[], char **env);
void	child_process(char *file_name, char *cmd, int pipe_fd[], char **env);
int		main(int ac, char **av, char **env);
#endif