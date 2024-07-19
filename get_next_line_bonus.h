/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahentton <ahentton@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:21:46 by ahentton          #+#    #+#             */
/*   Updated: 2024/07/19 13:51:13 by ahentton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <stdio.h>

char		*get_next_line(int fd);
char		*gnl_strjoin(char *s1, char *s2);
int			gnl_findnl(const char *str, char c);
void		*gnl_calloc(size_t count, size_t size);
void		*free_null(char **str, char **str2);
size_t		gnl_strlen(const char *str);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

#endif
