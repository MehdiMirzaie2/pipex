/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 12:57:21 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/09/08 11:09:19 by mmirzaie         ###   ########.fr       */
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
# include <stdbool.h>

#define MAX_PROCESS_NUM 100

typedef struct s_args{
	char	**av;
	int		ac;
	int		process_num;
	char	**env;
	int		*pids;
	bool	temp_file_created;
}	t_args;


// redirects
int		redirect_input(int from, int to);
int		redirect_output(int from, int to);

void	pipex(char *cmd, char **env);
void	found_error(char *str, int error);
char	*get_paths(char **env);
char	*ft_strcat(char *path, char *cmd);
char	*cmd_path(char **splitted_paths, char *cmd);
void	free_split_paths(char **splitted_paths);

#endif