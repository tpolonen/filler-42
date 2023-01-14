/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpolonen <tpolonen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 18:57:33 by tpolonen          #+#    #+#             */
/*   Updated: 2022/10/12 20:00:35 by tpolonen         ###   ########.fr       */
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

typedef struct s_margin
{
	int	top;
	int	right;
	int	bottom;
	int	left;
}	t_margin;

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
	t_margin	margin;
	char		*ptr;
	t_dintarr	*shape;
}	t_piece;

typedef struct s_strategy
{
	char		*enemy;
	char		*player;
	char		*target_ptr;
	int			*values_ptr;
	t_dintarr	*target_shape;
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
