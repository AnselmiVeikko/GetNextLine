/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahentton <ahentton@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:22:40 by ahentton          #+#    #+#             */
/*   Updated: 2024/06/24 15:21:20 by ahentton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdint.h>

size_t	gnl_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	*free_null(char **str)
{
	free (*str);
	*str = NULL;
	return (NULL);
}

void	*gnl_calloc(size_t count, size_t size)
{
	void	*p;
	size_t	i;
	char	*str;
	size_t	limit;

	limit = SIZE_MAX;
	if (count > 0 && size > limit / count)
		return (NULL);
	p = malloc (count * size);
	if (p == 0)
		return (NULL);
	str = (char *) p;
	i = 0;
	while (i < (count * size))
	{
		str[i] = '\0';
		i++;
	}
	return (p);
}

int	gnl_strchr(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*ret;
	int		i;
	int		j;
	int		sizetotal;

	if (!s1)
		return (NULL);
	sizetotal = (gnl_strlen(s1) + gnl_strlen(s2));
	ret = gnl_calloc(sizeof(char), sizetotal + 1);
	if (ret == NULL)
		return (free_null(&s1));
	i = 0;
	while (s1[i] != '\0')
	{
		ret[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		ret[i + j] = s2[j];
		j++;
	}
	free_null(&s1);
	return (ret);
}
