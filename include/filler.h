/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpolonen <tpolonen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 19:16:22 by tpolonen          #+#    #+#             */
/*   Updated: 2022/10/12 19:54:27 by tpolonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

/* read, write */
# ifndef WIN
#  include <unistd.h>
# else
#  include <Windows.h>
# endif

/* malloc, read */
# include <stdlib.h>

/* perror */
# include <stdio.h>

/* size_t, ssize_t */
# if defined (LINUX) || defined (WIN)
#  include <stdint.h>
# endif

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
	int		turncount;
	char	*oboard_ptr;
	char	*xboard_ptr;
	char	*temp;
}	t_data;

typedef struct s_strategy
{
	char		*enemy;
	char		*player;
	t_dintarr	*target;
	int			enemy_score;
	int			victory;
}	t_strat;

/* main.c */
int			init_data(t_data *data);

/* utils.c */
int			count(char *ptr, size_t n);
int			comp(char *ptr1, char *ptr2, size_t n);
int			comp1(char *ptr1, char *ptr2, size_t n);
void		*xalloc(size_t min_size);

/* read.c */
int			can_read_board(t_data *data);
int			can_read_piece(t_data *data, t_piece *piece);

/* debug.c */
void		debug_print(char *ptr, int width, int height);

/* player.c */
t_strat		*get_strat(void);
void		strategize(t_data *data);


/* tactics.c */
int			get_new_target(t_strat *strat);

/* floodfill.c */
t_dintarr	*floodfill(char *board, t_dintarr *source, int filled,
				size_t max_area);

/* storage.c */
t_strat		*get_strat(void);
t_data		*get_data(void);
t_piece		*get_piece(void);

#endif
