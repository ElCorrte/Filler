#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yzakharc <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/26 20:58:13 by yzakharc          #+#    #+#              #
#    Updated: 2017/06/29 18:28:42 by yzakharc         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = filler

all:
	gcc -Wall -Wextra -Werror filler.c -o $(NAME) libft/libft.a

clean:
	rm -rf *.o
	make clean -C ./libft

fclean: clean
	rm -rf $(NAME)

re: fclean all