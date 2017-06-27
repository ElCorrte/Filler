/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzakharc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 16:49:39 by yzakharc          #+#    #+#             */
/*   Updated: 2017/05/31 16:49:40 by yzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_LIBRARY_H
# define FILLER_LIBRARY_H

# include "libft/libft.h"

typedef struct	s_fil
{
	char		me;
	int 		map_x;
	int 		map_y;
	int 		play_x;
	int 		play_y;
	int 		piece_x;
	int 		piece_y;
	char 		**map;
	char 		**piece;
}				t_fil;

t_fil			fil;

void	filler(int i);

#endif
