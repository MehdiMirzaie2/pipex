/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:46:34 by mehdimirzai       #+#    #+#             */
/*   Updated: 2023/09/08 11:08:42 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	redirect_input(int from, int to)
{
	if (dup2(from, to) == -1)
		return (-1);
	if (close(from) == -1)
		return (-1);
	return (0);
}

int redirect_output(int from, int to)
{
	if (dup2(from, to) == -1)
		return (-1);
	if (close(from) == -1)
		return (-1);
	return (0);
}