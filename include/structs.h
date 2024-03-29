/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpolonen <tpolonen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 18:57:33 by tpolonen          #+#    #+#             */
/*   Updated: 2023/01/14 19:33:00 by tpolonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include "libft.h"

typedef struct s_coord
{
	int	x;
	int	y;
}	t_coord;

typedef struct s_rect
{
	int	x1;
	int	y1;
	int	x2;
	int	y2;
}	t_rect;

typedef struct s_gamedata
{
	char	player;
	int		width;
	int		height;
	char	*xboard_ptr;
	char	*oboard_ptr;
	char	*xoboard_ptr;
	char	*temp;
}	t_data;

typedef struct s_piece
{
	int			width;
	int			height;
	t_rect		rect;
	char		*ptr;
	t_dintarr	*shape;
}	t_piece;

typedef struct s_strategy
{
	char		*enemy;
	char		*player;
	char		*target_ptr;
	t_dintarr	*values_darr;
	t_dintarr	*target_shape;
	t_dintarr	*enemy_shape;
	int			free_space;
	int			turncount;
	int			enemy_score;
	int			victory;
}	t_strat;

typedef struct s_tactics
{
	t_dintarr	*source;
	t_dintarr	*valid_moves;
	t_dintarr	*enemy_hits;
	t_dintarr	*player_hits;
	t_dintarr	*juice_scores;
	t_dintarr	*distances;
}	t_tactics;

#endif
