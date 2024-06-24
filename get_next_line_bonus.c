/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahentton <ahentton@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:21:25 by ahentton          #+#    #+#             */
/*   Updated: 2024/06/24 16:01:26 by ahentton         ###   ########.fr       */
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

	if (s_buffer == NULL)
		return (NULL);
	buflen = gnl_strlen(s_buffer);
	nl_index = gnl_strchr(s_buffer, '\n');
	if (nl_index == -1)
		return (free_null(&s_buffer));
	rem_buffer = gnl_calloc((buflen - nl_index), sizeof(char));
	if (rem_buffer == NULL)
		return (free_null (&s_buffer));
	i = 0;
	nl_index++;
	while (s_buffer[nl_index] != '\0')
	{
		rem_buffer[i] = s_buffer[nl_index];
		i++;
		nl_index++;
	}
	free_null (&s_buffer);
	return (rem_buffer);
}

char	*trim_buffer(char *s_buffer)
{
	char	*line;
	int		nl_index;
	int		i;

	if (s_buffer == NULL)
		return (NULL);
	nl_index = gnl_strchr(s_buffer, '\n');
	if (nl_index == -1)
		nl_index = gnl_strlen(s_buffer);
	if (s_buffer[nl_index] == '\0')
		line = gnl_calloc(nl_index + 1, sizeof(char));
	else
		line = gnl_calloc(nl_index + 2, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (i < nl_index)
	{
		line[i] = s_buffer[i];
		if (line[i++] == '\n')
			return (line);
	}
	if (s_buffer[nl_index] == '\n')
		line[i] = '\n';
	return (line);
}

char	*read_fd(int fd, char *s_buffer)
{
	ssize_t	bytes_read;
	char	cup_buffer[BUFFER_SIZE + 1];

	if (!s_buffer)
		s_buffer = gnl_calloc(1, 1);
	if (s_buffer == NULL)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && s_buffer && gnl_strchr(s_buffer, '\n') == -1)
	{
		bytes_read = read (fd, cup_buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			if (s_buffer[0] == '\0')
				return (free_null(&s_buffer));
			break ;
		}
		cup_buffer[bytes_read] = '\0';
		s_buffer = gnl_strjoin(s_buffer, cup_buffer);
	}
	return (s_buffer);
}

char	*get_next_line(int fd)
{
	static char	*s_buffer[FOPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
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
		free_null(&s_buffer[fd]);
		s_buffer[fd] = NULL;
		return (NULL);
	}
	s_buffer[fd] = rem_buffer(s_buffer[fd]);
	if (s_buffer[fd] == NULL)
		free_null(&s_buffer[fd]);
	return (line);
}
