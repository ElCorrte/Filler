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

void	create_map(char *line, t_fil *fil, int fd)
{
	char	*tmp;

	!fil->map ? fil->map = ft_strnew(0) : 0;
	tmp = fil->map;
	fil->map = ft_strjoin(fil->map, line);
	free(tmp);
}

void	detect_map(char *line, t_fil *fil)
{
	fil->map_x = ft_atoi(line);
	fil->map_y = ft_atoi(line + 3);
}

void	detect_player(char *c, t_fil *fil)
{
	fil->me = (char) (*c == '1' ? 'O' : 'X');
}

int		main(void)
{
	char	*line;
	int		fd;
	t_fil	fil;
	int 	y;
	int 	x;
	int 	cnt;

	y = 0;
	x = 0;
	cnt = 0;
	fd = open("test", O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		ft_strchr(line, '$') ? detect_player(line + 10, &fil) : 0;
		!ft_strncmp(line, "Plateau", 7) ? detect_map(line + 7, &fil) : 0;
		ft_isdigit(*line) ? create_map(line + 4, &fil, fd) : 0;
		ft_strdel(&line);
	}
	while (x < fil.map_x)
	{
		while(y < fil.map_y)
		{
			ft_printf("%c", fil.map[cnt]);
			cnt++;
			y++;
		}
		y = 0;
		ft_printf("\n");
		x++;
	}
	free(fil.map);
	return (0);
}

//./resources/filler_vm -p1 ./cmake-build-debug/filler -p2 ./resources/players/abanlin.filler -v -f ./resources/maps/map00
