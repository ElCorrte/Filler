/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzakharc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 17:32:38 by yzakharc          #+#    #+#             */
/*   Updated: 2017/05/31 17:32:43 by yzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "filler.h"
#include <stdio.h>

int 	module_int(int digit)
{
	digit < 0 ? digit *= -1 : 0;
	return (digit);
}

void	find_better_place(int x, int y, int place_1, int place_2)
{
	static int	*good;
	int 		*bad;

	if (firth == 0)
	{
		!good ? good = ft_memalloc(1) : 0;
		good[0] = module_int(place_1 - x);
		good[1] = module_int(place_2 - y);
		firth++;
	}
	bad = ft_memalloc(1);
	bad[0] = module_int(place_1 - x);
	bad[1] = module_int(place_2 - y);
	if (good[0] > bad[0] || good[1] > bad[1])
	{
		good[0] = bad[0];
		good[1] = bad[1];
	}
	free(bad);
	fil.print_x = module_int(place_1 - good[0]);
	fil.print_y = module_int(place_2 - good[1]);
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

void 	clear_array(char **array, int len)
{
	int	cnt;

	cnt = len;
	while (cnt--)
		ft_strdel(&array[cnt]);
	free(array);
}

void	find_coord_map()
{
	int ok;
	int play_x;
	int play_y;

	play_y = -1;
	play_x = -1;
	while (++play_x < fil.map_x - fil.piece_x)
	{
		while (++play_y  < fil.map_y - fil.piece_y)
		{

			ok = check_piece(play_x, play_y);
			if (ok == 1)
			{
				find_better_place(play_x, play_y, fil.map_x - 1, fil.map_y - 1);
			}
		}
		play_y = -1;
	}
	clear_array(fil.map, fil.map_x);
	clear_array(fil.piece, fil.piece_x);
	firth = 0;
	ft_printf("%d %d\n", fil.print_x, fil.print_y);
}

void	detect_map(char *line)
{
	int	len;

	fil.map_x = ft_atoi(line);
	len = len_value(fil.map_x);
	fil.map_y = ft_atoi(line + (len + 1));
	len = -2;
	fil.map = (char **)malloc(sizeof(char *) * fil.map_x);
	while (++len < fil.map_x && get_next_line(0, &line))
	{
		dprintf(g_fd, "%s\n", line);
		ft_isdigit(*line) ? fil.map[len] = ft_strdup(line + 4) : 0;
		ft_strdel(&line);
	}
}

void 	detect_piece(char *line)
{
	int len;

	fil.piece_x = ft_atoi(line);
	len = len_value(fil.piece_x);
	fil.piece_y = ft_atoi(line + (len + 1));
	len = -1;
	fil.piece = (char **)malloc(sizeof(char *) * fil.piece_x);
	while (++len < fil.piece_x && get_next_line(0, &line))
	{
		dprintf(g_fd, "%s\n", line);
		fil.piece[len] = ft_strdup(line);
		ft_strdel(&line);
	}
	find_coord_map();
}

int		main(void)
{
	char	*line;

	line = NULL;
	g_fd = open("test", O_WRONLY);
	//g_fd = 0;
	while (get_next_line(0, &line))
	{
		dprintf(g_fd, "%s\n", line);
		if (ft_strchr(line, '$'))
		{
			fil.mine = (char) (*(line + 10) == '1' ? 'O' : 'X');
			fil.enemy = (char) (fil.mine == 'O' ? 'X' : 'O');
		}
		if (!ft_strncmp(line, "Plateau", 7))
			detect_map(line + 7);
		else if (!ft_strncmp(line, "Piece", 5))
			detect_piece(line + 5);
		ft_strdel(&line);
	}
	return (0);
}
