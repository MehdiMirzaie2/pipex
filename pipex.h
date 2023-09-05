/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 12:57:21 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/09/05 16:51:49 by mehdimirzai      ###   ########.fr       */
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

typedef struct s_args{
	char	**av;
	int		ac;
	int		process_num;
	char	**env;
}	t_args;

void	pipex(char *cmd, char **env);
void	found_error(char *str, int error);
char	*get_paths(char **env);
char	*ft_strcat(char *path, char *cmd);
char	*cmd_path(char **splitted_paths, char *cmd);
void	free_split_paths(char **splitted_paths);
#endif