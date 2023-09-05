/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:01:13 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/09/05 19:36:15 by mehdimirzai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*convert;
	char	character;

	convert = (char *)s;
	character = (char)c;
	i = ft_strlen(convert);
	while (i >= 0)
	{
		if (convert[i] == character)
			return (&convert[i]);
		i--;
	}
	return (0);
}

int	ft_strrchrpos(const char *s, int c)
{
	int		i;
	char	*convert;
	char	character;

	convert = (char *)s;
	character = (char)c;
	i = ft_strlen(convert);
	while (i >= 0)
	{
		if (convert[i] == character)
			return (i);
		i--;
	}
	return (0);
}