/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzakharc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 16:49:39 by yzakharc          #+#    #+#             */
/*   Updated: 2017/05/31 16:49:40 by yzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_LIBRARY_H
# define FILLER_LIBRARY_H

# include "libft/libft.h"

typedef struct	s_fil
{
	char		mine;
	char 		enemy;
	int 		map_x;
	int 		map_y;
	int 		piece_x;
	int 		piece_y;
	int 		print_x;
	int 		print_y;
	int 		must_print;
	int 		move_x;
	int 		move_y;
	int 		firth;
	char 		**map;
	char 		**piece;
}				t_fil;

t_fil			fil;
int				g_fd;

void			where_to_go();
void			find_better_place(int x, int y, int place_1, int place_2);
int				check_piece(int play_x, int play_y);

#endif
