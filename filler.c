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
	fil.firth = 0;
	fil.must_print = -1;
	dprintf(g_fd, "firth = 0 !OK! :)\n");
	while (++play_x <= fil.map_x - fil.piece_x)
	{
		while (++play_y  <= fil.map_y - fil.piece_y)
		{
			ok = check_piece(play_x, play_y);
			if (ok == 1)
			{
				where_to_go(1);
				find_better_place(play_x, play_y, fil.move_x, fil.move_y);
			}
		}
		play_y = -1;
	}
	clear_array(fil.map, fil.map_x);
	clear_array(fil.piece, fil.piece_x);
	fil.must_print == 1 ? ft_printf("%d %d\n", fil.print_x, fil.print_y) : ft_printf("0 0\n");
	dprintf(g_fd, "prin : x y %d %d\n", fil.print_x, fil.print_y);
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
