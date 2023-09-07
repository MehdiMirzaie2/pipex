/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:22:41 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/04/04 11:15:36 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// unsigned long is used to ensure that the value of the pointer can be stored

char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != (unsigned char)c)
		++s;
	if (*s == (unsigned char)c)
		return ((char *)(unsigned long)s);
	else
		return (0);
}

size_t	ft_strlen(char const *str)
{
	char const	*ptr;

	ptr = str;
	while (*ptr)
		++ptr;
	return ((size_t)(ptr - str));
}

char	*ft_strdup(char const *str)
{
	char	*dup;
	char	*ptr;

	dup = malloc(sizeof(*dup) * (ft_strlen(str) + 1));
	if (!dup)
		return (NULL);
	ptr = dup;
	while (*str)
		*ptr++ = *str++;
	*ptr = 0;
	return (dup);
}

char	*ft_strjoin_and_free_old_temp(char *temp, const char *buf)
{
	char	*new_temp;
	char	*ptr_to_new_temp;
	char	*ptr_to_temp;

	new_temp = malloc((ft_strlen(temp) + ft_strlen(buf) + 1));
	if (!new_temp)
	{
		free (temp);
		return (NULL);
	}
	ptr_to_new_temp = new_temp;
	ptr_to_temp = temp;
	while (*ptr_to_temp)
		*ptr_to_new_temp++ = *ptr_to_temp++;
	while (*buf)
		*ptr_to_new_temp++ = *buf++;
	*ptr_to_new_temp = 0;
	free (temp);
	return (new_temp);
}

char	*ft_substr(const char *str, unsigned int start, size_t size)
{
	size_t	len;
	char	*substr;

	len = ft_strlen(str);
	if (start >= len)
		return (ft_strdup(""));
	if (len - start < size)
		size = len - start;
	substr = malloc(sizeof(*substr) * (size + 1));
	if (!substr)
		return (NULL);
	substr[size] = 0;
	while (size--)
		substr[size] = str[start + size];
	return (substr);
}
