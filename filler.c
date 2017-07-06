/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzakharc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 17:32:38 by yzakharc          #+#    #+#             */
/*   Updated: 2017/05/31 17:32:43 by yzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	clear_array(char **array, int len)
{
	int	cnt;

	cnt = len;
	while (cnt--)
		ft_strdel(&array[cnt]);
	free(array);
}

void	find_coord_map(void)
{
	int play_x;
	int play_y;

	play_x = -1;
	g_fil.firth = 0;
	g_fil.must_print = -1;
	while (++play_x <= g_fil.map_x - g_fil.piece_x)
	{
		play_y = -1;
		while (++play_y <= g_fil.map_y - g_fil.piece_y)
		{
			if (check_piece(play_x, play_y))
			{
				where_to_go();
				find_better_place(play_x, play_y, g_fil.move_x, g_fil.move_y);
			}
		}
	}
	clear_array(g_fil.map, g_fil.map_x);
	clear_array(g_fil.piece, g_fil.piece_x);
	g_fil.must_print == 1 ? ft_printf("%d %d\n", g_fil.print_x, g_fil.print_y) :
	ft_printf("0 0\n");
}

void	detect_map(char *line)
{
	int	len;

	g_fil.map_x = ft_atoi(line);
	len = len_value(g_fil.map_x);
	g_fil.map_y = ft_atoi(line + (len + 1));
	len = -2;
	g_fil.map = (char **)malloc(sizeof(char *) * g_fil.map_x);
	while (++len < g_fil.map_x && get_next_line(0, &line))
	{
		ft_isdigit(*line) ? g_fil.map[len] = ft_strdup(line + 4) : 0;
		ft_strdel(&line);
	}
}

void	detect_piece(char *line)
{
	int len;

	g_fil.piece_x = ft_atoi(line);
	len = len_value(g_fil.piece_x);
	g_fil.piece_y = ft_atoi(line + (len + 1));
	len = -1;
	g_fil.piece = (char **)malloc(sizeof(char *) * g_fil.piece_x);
	while (++len < g_fil.piece_x && get_next_line(0, &line))
	{
		g_fil.piece[len] = ft_strdup(line);
		ft_strdel(&line);
	}
	find_coord_map();
}

int		main(void)
{
	char	*line;

	line = NULL;
	while (get_next_line(0, &line))
	{
		if (ft_strchr(line, '$'))
		{
			g_fil.mine = (char)(*(line + 10) == '1' ? 'O' : 'X');
			g_fil.enemy = (char)(g_fil.mine == 'O' ? 'X' : 'O');
		}
		if (!ft_strncmp(line, "Plateau", 7))
			detect_map(line + 7);
		else if (!ft_strncmp(line, "Piece", 5))
			detect_piece(line + 5);
		ft_strdel(&line);
	}
	return (0);
}
