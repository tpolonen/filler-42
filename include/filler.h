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

/* size_t, ssize_t on non-cluster machines*/
# if defined (LINUX) || defined (WIN)
#  include <stdint.h>
#  include <limits.h>
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

/* navigator.c */
int			can_read_board(t_data *data, t_dintarr *enemy_shape);
int			can_read_piece(t_data *data, t_piece *piece);
int			set_player(t_data *data);
int			init_data(t_data *data);

/* strategist.c */
void		strategize(t_data *data);

/* tactician.c */
void		find_new_target(t_strat *strat);
int			*get_values(char *board, t_dintarr *shape);

/* captain.c */
int			valid_move_exists();

/* floodfill.c */
t_dintarr	*floodfill(char *board, t_dintarr *source, int wall,
				size_t max_area);
/* storage.c */
t_strat		*get_strat(void);
t_data		*get_data(void);
t_piece		*get_piece(void);
t_dintarr 	*get_enemy_shape(void);

/* utils.c */
int			clean_exit(t_data *data, const char *str, int error);
int			comp(char *ptr1, char *ptr2, size_t n);
int			comp1(char *ptr1, char *ptr2, size_t n);
void		*xalloc(size_t min_size);

/* debug.c */
void		debug_print(char *ptr, int width, int height);

#endif
