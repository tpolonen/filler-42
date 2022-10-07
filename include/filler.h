/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpolonen <tpolonen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 19:16:22 by tpolonen          #+#    #+#             */
/*   Updated: 2022/10/07 18:40:11 by tpolonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

/*
 * read, write
 */
# include <unistd.h>

/*
 * malloc, read
 */
# include <stdlib.h>

/*
 * perror
 */
# include <stdio.h>

# include "libft.h"

typedef struct s_piece
{
	int		width;
	int		height;
	char	*ptr;
}	t_piece;

typedef struct s_gamedata
{
	char	player;
	int		width;
	int		height;
	char	*oboard_ptr;
	char	*xboard_ptr;
	char	*temp;
}	t_data;

/*
 * utils.c
 */
void	*xalloc(size_t min_size);
int		comp(char *ptr1, char *ptr2, size_t n);

/*
 * read.c
 */
int		read_board(t_data *data);
int		read_piece(t_data *data, t_piece *piece);

/*
 * debug.c
 */
void	debug_print(char *ptr, int width, int height);

/*
 * player.c
 */
int		make_move(t_data *data, t_piece *piece);

#endif
