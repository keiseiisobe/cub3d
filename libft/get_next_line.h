/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisobe <kisobe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 10:51:01 by kisobe            #+#    #+#             */
/*   Updated: 2024/02/09 08:46:06 by kisobe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdint.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*free_buf(char *buf);
void	*join_bufs(char *s1, char *s2);
int		ft_strsearch(char *str, char c);
void	ft_buf_zero(char *buf);
size_t	ft_str_line_len(char *str, char c);
char	*ready_for_next(char *buf);
char	*after_read(char **buf_p, char *buf_tmp, int flag_checking_line,
			ssize_t bytes);
char	*ft_strndup(char *str, size_t len);
void	*ft_calloc(size_t count, size_t size);

#endif
