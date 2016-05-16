# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jplevy <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/10 13:21:18 by jplevy            #+#    #+#              #
#    Updated: 2016/05/10 23:34:55 by joeyplevy        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = gcc
CFLAG = -c -Wall -Werror -Wextra
SRC_NAME = 
OBJ_NAME = $(SRC_NAME:.c=.o)
LIBFT_PATH = ./libft/
LIBFT_NAME = libft.a
RM = rm -f

all: $(NAME)

$(NAME):
	@$(MAKE) -C $(LIBFT_PATH)
	@$(CC) $(CFLAGS) $(SRC_NAME)
	@$(CC) $(OBJ_NAME) -L. $(LIBFT_PATH)$(LIBFT_NAME) -o $(NAME)
clean:
	@$(MAKE) -C $(LIBFT_PATH) clean
	@$(RM) $(OBJ_NAME)

fclean: clean
	@$(MAKE) -C $(LIBFT_PATH) fclean
	@$(RM) $(NAME)

re: fclean all