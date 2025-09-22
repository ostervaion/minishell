/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juetxeba <juetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:59:15 by juetxeba          #+#    #+#             */
/*   Updated: 2025/05/06 17:25:18 by juetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include "libft.h"

char	*get_next_line(int fd);
void	ft_printable(char **saved_l, char **line);
char	*ft_strdupgnl(char *s);
void	ft_strjoingnl(char **saved_l, char *buffer);
char	*ft_last_line(char **saved_l);

#endif
