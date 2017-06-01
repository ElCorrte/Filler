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

void	print_map_piece(char *str, int crdn_x, int crdn_y)
{
	int 	y;
	int 	x;
	int 	cnt;

	y = -1;
	x = -1;
	cnt = 0;
	while (++x < crdn_x)
	{
		while(++y < crdn_y)
			ft_printf("%c", str[cnt++]);
		y = -1;
		ft_printf("\n");
	}
}

char	*create_map_piece(char *line, char *str)
{
	char	*tmp;
	char 	*dst;
	char 	*temp;

	if (str != NULL)
	{
		temp = str;
		dst = ft_strdup(str);
		free(temp);
	}
	else
		dst = ft_strnew(0);
	tmp = dst;
	dst = ft_strjoin(dst, line);
	free(tmp);
	return (dst);
}

void	detect_map(char *line, t_fil *fil, int fd)
{
	int	len;

	fil->map != NULL ? ft_strdel(&fil->map) : 0;
	fil->map_x = ft_atoi(line);
	len = len_value(fil->map_x);
	fil->map_y = ft_atoi(line + (len + 1));
	len = -2;
	while (++len < fil->map_x)
	{
		get_next_line(fd, &line);
		ft_isdigit(*line) ? fil->map = create_map_piece(line + 4, fil->map) : 0;
		ft_strdel(&line);
	}
	print_map_piece(fil->map, fil->map_x, fil->map_y);
}

void	detect_player(char *c, t_fil *fil)
{
	fil->me = (char) (*c == '1' ? 'O' : 'X');
}


void 	detect_piece(char *line, t_fil *fil, int fd)
{
	int len;

	fil->piece != NULL ? ft_strdel(&fil->piece) : 0;
	fil->piece_x = ft_atoi(line);
	len = len_value(fil->piece_x);
	fil->piece_y = ft_atoi(line + (len + 1));
	len = -1;
	while (++len < fil->piece_x)
	{
		get_next_line(fd, &line);
		fil->piece = create_map_piece(line, fil->piece);
		ft_strdel(&line);
	}
	print_map_piece(fil->piece, fil->piece_x, fil->piece_y);
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
	//while (1);
	return (0);
}

//./resources/filler_vm -p1 ./cmake-build-debug/filler -p2 ./resources/players/abanlin.filler -v -f ./resources/maps/map00
