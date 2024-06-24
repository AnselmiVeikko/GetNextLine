/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahentton <ahentton@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:39:15 by ahentton          #+#    #+#             */
/*   Updated: 2024/06/10 16:10:55 by ahentton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

char		*get_next_line(int fd);
char		*gnl_strjoin(char *s1, char *s2);
int			gnl_strchr(const char *str, char c);
void		*gnl_calloc(size_t count, size_t size);
void		*free_null(char **str);
size_t		gnl_strlen(const char *str);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

#endif
