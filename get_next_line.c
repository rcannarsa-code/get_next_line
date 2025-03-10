/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcannars <rcannars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 17:54:22 by rcannars          #+#    #+#             */
/*   Updated: 2024/12/27 14:46:23 by rcannars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*join_buffer(char *joined, char *buffer, ssize_t bytes_read)
{
	char	*temp;

	if (bytes_read <= 0)
	{
		if (bytes_read < 0 || !*joined)
		{
			free(joined);
			return (NULL);
		}
		return (joined);
	}
	buffer[bytes_read] = '\0';
	temp = gnl_smart_strjoin(joined, buffer, 1, 0);
	if (!temp)
	{
		free(joined);
		return (NULL);
	}
	return (temp);
}

char	*read_and_join(char *stash, int fd)
{
	char	*joined;
	ssize_t	bytes_read;
	char	*buffer;

	buffer = malloc(BUFFER_SIZE + 1);
	buffer[0] = '\0';
	joined = gnl_smart_strjoin("", stash, 0, 0);
	if (!joined)
	{
		free(buffer);
		return (NULL);
	}
	while (!check_new_line(joined))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		joined = join_buffer(joined, buffer, bytes_read);
		if (!joined || bytes_read == 0)
			break ;
	}
	free(buffer);
	return (joined);
}

char	*extract_line(char *line)
{
	char	*next_line;
	size_t	len_line;
	size_t	i;

	len_line = 0;
	while (line[len_line] != '\n' && line[len_line] != '\0')
		len_line++;
	next_line = malloc(len_line + 2);
	if (!next_line)
		return (NULL);
	i = 0;
	while (i <= len_line)
	{
		next_line[i] = line[i];
		i++;
	}
	if (line[len_line] == '\n')
		next_line[i - 1] = '\n';
	next_line[i] = '\0';
	return (next_line);
}

void	extract_stash(const char *line, char *stash)
{
	size_t	len_line;
	size_t	i;

	len_line = 0;
	i = 0;
	while (line[len_line] != '\n' && line[len_line] != '\0')
		len_line++;
	if (line[len_line] == '\n')
		len_line++;
	while (line[len_line])
	{
		stash[i] = line[len_line];
		i++;
		len_line++;
	}
	stash[i] = '\0';
}

char	*get_next_line(int fd)
{
	static char	stash[BUFFER_SIZE];
	char		*line;
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = read_and_join(stash, fd);
	if (!line)
		return (NULL);
	next_line = extract_line(line);
	if (!next_line)
	{
		free(line);
		return (NULL);
	}
	extract_stash(line, stash);
	free(line);
	return (next_line);
}
