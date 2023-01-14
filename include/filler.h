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
# include "structs.h"

/* scout.c */
int			init_data(t_data *data);
int			can_read_board(t_data *data, t_dintarr *enemy_shape);
int			can_read_piece(t_data *data, t_piece *piece);
int			set_player(t_data *data);

/* strategist.c */
void		strategize(t_data *data);

/* tactician.c */
void		find_new_target(t_strat *strat);
int			*get_values(t_dintarr *shape);

/* captain.c */
int			get_next_move(void);

/* counters.c */
int			count(char *left, char *right, int n);
void		count_board_matches(t_piece *piece, char *board, t_dintarr *out);
int			find_juiciest_cell(t_tactics *tactics);
int			find_closest_cell(t_tactics *tactics);

/* floodfill.c */
t_dintarr	*floodfill(t_dintarr **root, char *board,
		int wall, size_t max_area);

/* storage.c */
t_data		*get_data(void);
t_strat		*get_strat(void);
t_piece		*get_piece(void);
t_dintarr	*get_enemy_shape(void);
t_tactics	*get_tactics(void);

/* utils.c */
int			clean_exit(t_data *data, const char *str, int error);
void		find_margins(void);
void		*xalloc(size_t min_size);

/* debug.c */
void		debug_print(char *ptr, int width, int height);

#endif
