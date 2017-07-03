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

	if (fil.firth == 0)
	{
		dprintf(g_fd, "MOVE it: %d %d\n", place_1, place_2);
		good = module_int(x - place_1) + module_int(y - place_2);
		fil.print_x = x;
		fil.print_y = y;
		dprintf(g_fd, "good : %d\n", good);
		fil.firth++;
	}
	bad = module_int(x - place_1) + module_int(y - place_2);
	dprintf(g_fd, "bad  : %d\n", bad);
	if (bad <= good)
	{
		good = bad;
		dprintf(g_fd, "new_good : %d\n", good);
		fil.print_x = x;
		fil.print_y = y;
		fil.must_print = 1;
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

int		check_the_point_of_the_move(int x, int y, int radius)
{
	int	i;
	int j;
	int end_x;
	int end_y;

	end_x = x + radius > fil.map_x - 1 ? fil.map_x - 1 : x + radius;
	end_y = y + radius > fil.map_y - 1 ? fil.map_y -1 : y + radius;
	i = x - radius;
	j = y - radius;
	i < 0 ? i = x : 0;
	j < 0 ? j = y : 0;
	while (i <= end_x)
	{
		while (j <= end_y)
		{
			if (fil.map[i][j] == fil.mine || fil.map[i][j] == fil.enemy)
				return (0);
			j++;
		}
		j = y - radius;
		j < 0 ? j = y : 0;
		i++;
	}
	fil.move_x = x;
	fil.move_y = y;
	return (1);
}

void	where_to_go()
{
	int rad;

	rad = 0;
	rad = fil.map_y == 40 ? 3 : 0;
	rad = fil.map_y == 100 ? 5 : 0;
	//if (check_the_point_of_the_move(fil.map_x / 2, fil.map_y / 2, rad));
	if (check_the_point_of_the_move(fil.map_x / 2, 0, rad));
	else if (check_the_point_of_the_move(0, fil.map_y / 2, rad));
	else if (check_the_point_of_the_move(fil.map_x / 2, fil.map_y - 1, rad));
	else if (check_the_point_of_the_move(fil.map_x - 1, fil.map_y / 2, rad));
	else if (check_the_point_of_the_move(0, fil.map_y - 1, rad));
	else if (check_the_point_of_the_move(0, 0, rad));
	else if (check_the_point_of_the_move(fil.map_x - 1, 0, rad));
	else if (check_the_point_of_the_move(fil.map_x - 1, fil.map_y - 1, rad));
	else if (check_the_point_of_the_move(fil.map_x - 1, fil.map_y - 1, rad));
	else
	{
		fil.move_x = fil.map_x / 2;
		fil.move_y = fil.map_y / 2;
	}
}
