/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahentton <ahentton@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:21:25 by ahentton          #+#    #+#             */
/*   Updated: 2024/07/19 13:27:59 by ahentton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>

char	*rem_buffer(char *s_buffer)
{
	char	*rem_buffer;
	int		nl_index;
	int		buflen;
	int		i;

	buflen = gnl_strlen(s_buffer);
	nl_index = gnl_findnl(s_buffer, '\n');
	if (nl_index == -1)
		return (free_null(&s_buffer, 0));
	rem_buffer = gnl_calloc((buflen - nl_index), sizeof(char));
	if (rem_buffer == NULL)
		return (free_null (&s_buffer, 0));
	i = 0;
	nl_index++;
	while (s_buffer[nl_index] != '\0')
	{
		rem_buffer[i] = s_buffer[nl_index];
		i++;
		nl_index++;
	}
	free_null (&s_buffer, 0);
	return (rem_buffer);
}

char	*trim_buffer(char *s_buffer)
{
	char	*line;
	int		line_len;
	int		i;

	line_len = gnl_findnl(s_buffer, '\n');
	if (line_len == -1)
		line_len = gnl_strlen(s_buffer);
	if (s_buffer[line_len] == '\0')
		line = gnl_calloc(line_len + 1, sizeof(char));
	else
		line = gnl_calloc(line_len + 2, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (i < line_len)
	{
		line[i] = s_buffer[i];
		i++;
	}
	if (s_buffer[line_len] == '\n')
		line[i] = '\n';
	return (line);
}

char	*read_fd(int fd, char *s_buffer)
{
	ssize_t	bytes_read;
	char	*cup_buffer;

	if (!s_buffer)
		s_buffer = gnl_calloc(1, 1);
	if (s_buffer == NULL)
		return (NULL);
	cup_buffer = gnl_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!cup_buffer)
		return (free_null(&s_buffer, 0));
	bytes_read = 1;
	while (bytes_read > 0 && s_buffer && gnl_findnl(s_buffer, '\n') == -1)
	{
		bytes_read = read (fd, cup_buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			if (s_buffer[0] == '\0')
				return (free_null(&s_buffer, &cup_buffer));
			break ;
		}
		cup_buffer[bytes_read] = '\0';
		s_buffer = gnl_strjoin(s_buffer, cup_buffer);
	}
	free (cup_buffer);
	return (s_buffer);
}

char	*get_next_line(int fd)
{
	static char	*s_buffer[FOPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0 || fd >= FOPEN_MAX)
	{
		if (s_buffer[fd] != NULL)
			free(s_buffer[fd]);
		s_buffer[fd] = NULL;
		return (NULL);
	}
	s_buffer[fd] = read_fd(fd, s_buffer[fd]);
	if (s_buffer[fd] == NULL)
		return (NULL);
	line = trim_buffer(s_buffer[fd]);
	if (line == NULL)
	{
		free_null(&s_buffer[fd], 0);
		s_buffer[fd] = NULL;
		return (NULL);
	}
	s_buffer[fd] = rem_buffer(s_buffer[fd]);
	if (s_buffer[fd] == NULL)
		free_null(&s_buffer[fd], 0);
	return (line);
}
