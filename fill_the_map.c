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

#include "filler.h"

void	find_better_place(int x, int y, int place_1, int place_2)
{
	static int	good;
	int			bad;

	if (g_fil.firth == 0)
	{
		good = ft_module_int(x - place_1) + ft_module_int(y - place_2);
		g_fil.print_x = x;
		g_fil.print_y = y;
		g_fil.firth++;
	}
	bad = ft_module_int(x - place_1) + ft_module_int(y - place_2);
	if (bad <= good)
	{
		good = bad;
		g_fil.print_x = x;
		g_fil.print_y = y;
		g_fil.must_print = 1;
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
	while (++cnt_x < g_fil.piece_x)
	{
		while (++cnt_y < g_fil.piece_y)
		{
			if (g_fil.map[play_x + cnt_x][play_y + cnt_y] == g_fil.mine &&
				g_fil.piece[cnt_x][cnt_y] == '*')
				cnt_place++;
			else if (g_fil.map[play_x + cnt_x][play_y + cnt_y] == g_fil.enemy &&
					g_fil.piece[cnt_x][cnt_y] == '*')
				return (0);
		}
		cnt_y = -1;
	}
	if (cnt_place > 1)
		return (0);
	return (cnt_place == 1 ? 1 : 0);
}

int		check_point_of_the_move(int x, int y, int radius)
{
	int	i;
	int j;
	int end_x;
	int end_y;

	end_x = x + radius > g_fil.map_x - 1 ? g_fil.map_x - 1 : x + radius;
	end_y = y + radius > g_fil.map_y - 1 ? g_fil.map_y - 1 : y + radius;
	i = x - radius < 0 ? x : x - radius;
	j = y - radius < 0 ? y : y - radius;
	while (i <= end_x)
	{
		while (j <= end_y)
		{
			if (g_fil.map[i][j] == g_fil.mine || g_fil.map[i][j] == g_fil.enemy)
				return (0);
			j++;
		}
		j = y - radius;
		j < 0 ? j = y : 0;
		i++;
	}
	g_fil.move_x = x;
	g_fil.move_y = y;
	return (1);
}

void	where_to_go(void)
{
	int rad;

	rad = 1;
	rad = g_fil.map_y == 100 ? 5 : 0;
	if (check_point_of_the_move(g_fil.map_x / 2, 0, rad))
		;
	else if (check_point_of_the_move(g_fil.map_x / 2, g_fil.map_y - 1, rad))
		;
	else if (check_point_of_the_move(0, g_fil.map_y / 2, rad))
		;
	else if (check_point_of_the_move(g_fil.map_x - 1, g_fil.map_y / 2, rad))
		;
	else if (check_point_of_the_move(0, g_fil.map_y - 1, rad))
		;
	else if (check_point_of_the_move(0, 0, rad))
		;
	else if (check_point_of_the_move(g_fil.map_x - 1, 0, rad))
		;
	else if (check_point_of_the_move(g_fil.map_x - 1, g_fil.map_y - 1, rad))
		;
	else
	{
		g_fil.move_x = g_fil.map_x / 2;
		g_fil.move_y = g_fil.map_y / 2;
	}
}
