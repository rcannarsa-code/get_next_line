/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcannars <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 14:47:45 by rcannars          #+#    #+#             */
/*   Updated: 2024/12/27 14:47:49 by rcannars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	check_new_line(char *buffer)
{
	size_t	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*gnl_smart_strjoin(char *s1, char *s2, int free1, int free2)
{
	char	*join;
	size_t	len1;
	size_t	len2;

	if (!s1 && !s2)
		return (NULL);
	len1 = gnl_strlen(s1);
	len2 = gnl_strlen(s2);
	join = malloc(len1 + len2 + 1);
	if (!join)
		return (NULL);
	gnl_strlcpy(join, s1, len1 + 1);
	gnl_strlcat(join, s2, len1 + len2 + 1);
	if (free1)
		free(s1);
	if (free2)
		free(s2);
	return (join);
}

size_t	gnl_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	s_len;
	size_t	i;

	i = 0;
	s_len = gnl_strlen(src);
	if (size > 0)
	{
		while (src[i] != '\0' && i < size - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (s_len);
}

size_t	gnl_strlcat(char *dest, const char *src, size_t size)
{
	size_t	d_len;
	size_t	s_len;
	size_t	i;

	if (!dest && size == 0)
		return (gnl_strlen(src));
	d_len = 0;
	s_len = 0;
	i = 0;
	while (dest[d_len] && d_len < size)
	{
		d_len++;
	}
	s_len = gnl_strlen(src);
	if (d_len >= size)
		return (size + s_len);
	while (src[i] && (d_len + i + 1) < size)
	{
		dest[d_len + i] = src[i];
		i++;
	}
	dest[d_len + i] = '\0';
	return (d_len + s_len);
}
