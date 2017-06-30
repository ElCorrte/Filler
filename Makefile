#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yzakharc <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/26 20:58:13 by yzakharc          #+#    #+#              #
#    Updated: 2017/06/30 13:46:38 by yzakharc         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = filler
SRC =	./filler.c\
		./fill_the_map.c
all:
	gcc -Wall -Wextra -Werror $(SRC) -o $(NAME) libft/libft.a

clean:
	rm -rf *.o
	make clean -C ./libft

fclean: clean
	rm -rf $(NAME)

re: fclean all