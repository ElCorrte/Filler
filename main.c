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

void	find_coord_map(t_fil *fil)
{
	int x;
	int y;

	x = fil->map_x + 1;
	y = fil->map_y + 1;


}

char	*create_map_piece(char *line)
{
	char 	*dst;

	dst = ft_strdup(line);
	return (dst);
}

void	detect_map(char *line, t_fil *fil, int fd)
{
	int	len;

	fil->map != NULL ? ft_strdel(fil->map) : 0;
	fil->map_x = ft_atoi(line);
	len = len_value(fil->map_x);
	fil->map_y = ft_atoi(line + (len + 1));
	len = -2;
	fil->map = (char **)malloc(sizeof(char *) * fil->map_x);
	while (++len < fil->map_x)
	{
		get_next_line(fd, &line);
		ft_isdigit(*line) ? fil->map[len] = create_map_piece(line + 4) : 0;
		ft_strdel(&line);
	}
	for (int x = 0; x < fil->map_x; x++)
	{
		ft_printf("%s\n", fil->map[x]);
	}
	find_coord_map(fil);
}

void	detect_player(char *c, t_fil *fil)
{
	fil->me = (char) (*c == '1' ? 'O' : 'X');
}


void 	detect_piece(char *line, t_fil *fil, int fd)
{
	int len;

	fil->piece != NULL ? ft_strdel(fil->piece) : 0;
	fil->piece_x = ft_atoi(line);
	len = len_value(fil->piece_x);
	fil->piece_y = ft_atoi(line + (len + 1));
	len = -1;
	fil->piece = (char **)malloc(sizeof(char *) * fil->piece_x);
	while (++len < fil->piece_x)
	{
		get_next_line(fd, &line);
		fil->piece[len] = create_map_piece(line);
		ft_strdel(&line);
	}
	for (int x = 0; x < fil->piece_x; x++)
		ft_printf("%s\n", fil->piece[x]);
}

int		main(void)
{
	char	*line;
	int		fd;
	t_fil	fil;

	//fd = 0;
	fd = open("test", O_RDONLY);
	while (get_next_line(fd, &line))
	{
		ft_strchr(line, '$') ? detect_player(line + 10, &fil) : 0;
		!ft_strncmp(line, "Plateau", 7) ? detect_map(line + 7, &fil, fd) : 0;
		!ft_strncmp(line, "Piece", 5) ? detect_piece(line + 5, &fil, fd) : 0;
		ft_strdel(&line);
	}
	return (0);
}

//./resources/filler_vm -p1 ./cmake-build-debug/filler -p2 ./resources/players/abanlin.filler -v -f ./resources/maps/map00
