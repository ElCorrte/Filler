#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yzakharc <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/26 20:58:13 by yzakharc          #+#    #+#              #
#    Updated: 2017/07/04 19:57:16 by yzakharc         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	=	filler
CC		=	gcc
FLAG	=	-Wall -Wextra -Werror
LIBFT	=	./libft/libft.a
OBJ     =   ./fill_the_map.o    \
            ./filler.o          \

.PHONY: libft

all : $(NAME)

$(NAME) : $(OBJ) libft
	$(CC) $(FLAG) -o $(NAME) $(OBJ) $(LIBFT)

libft:
	make -C ./libft

%.o : %.c
	$(CC) $(FLAG) -o $@ -c $<

clean:
	rm -rf $(OBJ)
	make clean -C ./libft

fclean: clean
	rm -rf $(NAME)
	make fclean -C ./libft

re: fclean all
