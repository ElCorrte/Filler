/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_the_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzakharc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/30 13:13:44 by yzakharc          #+#    #+#             */
/*   Updated: 2017/06/30 13:13:44 by yzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "filler.h"

int 	module_int(int digit)
{
	digit < 0 ? digit *= -1 : 0;
	return (digit);
}

void	find_better_place(int x, int y, int place_1, int place_2)
{
	static int	good;
	int 		bad;

	if (firth == 0)
	{
		good = module_int(x - place_1) + module_int(y - place_2);
		firth++;
	}
	bad = module_int(x - place_1) + module_int(y - place_2);
	if (bad <= good)
	{
		good = bad;
		fil.print_x = x;
		fil.print_y = y;
	}
}

int		check_piece(int play_x, int play_y)
{
	int cnt_x;
	int cnt_y;
	int cnt_place;

	cnt_x = -1;
	cnt_y = -1;
	cnt_place = 0;
	while (++cnt_x < fil.piece_x)
	{
		while (++cnt_y < fil.piece_y)
		{
			if (fil.map[play_x + cnt_x][play_y + cnt_y] == fil.mine &&
				fil.piece[cnt_x][cnt_y] == '*')
				cnt_place++;
			else if (fil.map[play_x + cnt_x][play_y + cnt_y] == fil.enemy &&
					 fil.piece[cnt_x][cnt_y] == '*')
				return (0);
		}
		cnt_y = -1;
	}
	if (cnt_place > 1)
		return (0);
	return (cnt_place == 1 ? 1 : 0);
}

int		check_the_point_of_the_movement(int x, int y, int radius)
{
	int	i;
	int j;

	i = x - radius;
	j = y - radius;
	i < 0 ? i = x : 0;
	j < 0 ? j = y : 0;
	while (i <= x + radius)
	{
		while (j <= y + radius)
		{
			if (fil.map[i][j] == fil.mine || fil.map[i][j] == fil.enemy)
				return (0);
			j++;
		}
		j = y - radius;
		j < 0 ? j = y : 0;
		i++;
	}
	return (1);
}

void	where_to_go()
{
	/*int radius;

	radius = 1;
	if (check_the_point_of_the_movement(fil.map_x / 2, fil.map_y / 2, radius))
	{
		fil.move_x = fil.map_x / 2;
		fil.move_y = fil.map_y / 2;
	}
	else if (check_the_point_of_the_movement(0, fil.map_y - 1, radius))
	{
		fil.move_x = 0;
		fil.move_y = fil.map_y - 1;
	}
	else if (check_the_point_of_the_movement(fil.map_x - 1, 0, radius))
	{
		fil.move_x = fil.map_x - 1;
		fil.move_y = 0;
	}
	else if (check_the_point_of_the_movement(fil.map_x -1, fil.map_y - 1, radius))
	{
		fil.move_x = fil.map_x - 1;
		fil.move_y = fil.map_y - 1;
	}
	else
	{*/
		fil.move_x = 0;
		fil.move_y = 0;
	//}
}
