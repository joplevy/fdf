/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 10:59:44 by jplevy            #+#    #+#             */
/*   Updated: 2016/04/30 03:34:04 by joeyplevy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 32

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/time.h>
# include "libft.h"

typedef struct			s_list_fd
{
	int					fd;
	char				*line;
	struct s_list_fd	*next;
}						t_list_fd;

int						ft_indexof(char *str);
int						get_chars(char *buff, char **str);
int						ft_result(char **line, char **str, int n);
int						get_next_line(int const fd, char **line);
t_list_fd				*ft_fd_finder(t_list_fd **mem, int fd);
#endif
