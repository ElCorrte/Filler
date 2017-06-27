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

int 	g_fd;

void 	print(char **str, int cord)
{
	//int	fd_me = open("print_me", O_WRONLY);

	for (int i = 0; i < cord; ++i)
		ft_printf("%s\n", str[i]);
}

int		check_piece(int play_x, int play_y)
{
	int cnt_x;
	int cnt_y;

	cnt_x = -1;
	cnt_y = -1;
	while (++cnt_x < fil.piece_x)
	{
		while (++cnt_y < fil.piece_y)
		{
			if (fil.map[play_x + cnt_x][play_y + cnt_y] == fil.me && fil.piece[cnt_x][cnt_y] == '*')
				return (1);
			//write(1, &fil.piece[cnt_x][cnt_y], 1);
			//write(1, &fil.map[play_x + cnt_x][play_y + cnt_y], 1);
		}
		//write(1, "\n", 1);
		cnt_y = -1;
	}
	return (0);
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
	while (++play_x < fil.map_x)
	{
		while (++play_y  < fil.map_y - fil.piece_y)
		{
			ok = check_piece(play_x, play_y);
			if (ok == 1)
			{
				clear_array(fil.map, fil.map_x);
				clear_array(fil.piece, fil.piece_x);
				printf("%d %d\n", play_x, play_y);
				return ;
			}
		}
		play_y = -1;
	}
}

void	detect_map(char *line)
{
	int	len;

	fil.map_x = ft_atoi(line);
	len = len_value(fil.map_x);
	fil.map_y = ft_atoi(line + (len + 1));
	len = -2;
	fil.map = (char **)malloc(sizeof(char *) * fil.map_x);
	while (++len < fil.map_x)
	{
		get_next_line(g_fd, &line);
		//dprintf(g_fd, "%s\n", line);
		ft_isdigit(*line) ? fil.map[len] = ft_strdup(line + 4) : 0;
		ft_strdel(&line);
	}
	print(fil.map, fil.map_x);
	//clear_array(fil.map, fil.map_x);
}

void 	detect_piece(char *line)
{
	int len;

	fil.piece_x = ft_atoi(line);
	len = len_value(fil.piece_x);
	fil.piece_y = ft_atoi(line + (len + 1));
	len = -1;
	fil.piece = (char **)malloc(sizeof(char *) * fil.piece_x);
	while (++len < fil.piece_x)
	{
		get_next_line(g_fd, &line);
		//dprintf(g_fd, "detect_piece: %s\n", line);
		fil.piece[len] = ft_strdup(line);
		ft_strdel(&line);
	}
	print(fil.piece, fil.piece_x);
	//clear_array(fil.piece, fil.piece_x);
	find_coord_map();
}

int		main(void)
{
	char	*line;

	line = NULL;
	g_fd = open("test", O_RDONLY);
	while (get_next_line(g_fd, &line))
	{
		//dprintf(g_fd, "%s\n", line);
		if (ft_strchr(line, '$'))
			fil.me = (char) (*(line + 10) == '1' ? 'O' : 'X');
		if (!ft_strncmp(line, "Plateau", 7))
			detect_map(line + 7);
		else if (!ft_strncmp(line, "Piece", 5))
			detect_piece(line + 5);
		ft_strdel(&line);
	}
	//while (1);
	return (0);
}

//./resources/filler_vm -p1 ./filler -p2 ./resources/players/abanlin.filler -v -f ./resources/maps/map00
