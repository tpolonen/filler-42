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

# ifdef DEBUG_ON
#  define DEBUG 1
# else
#  define DEBUG 0
# endif

# include "libft.h"
# include "structs.h"

/* scout.c */
int			can_read_board(t_data *data, t_strat *strat);
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
void		floodfill(t_tactics *tactics, t_strat *strat, char *board, size_t max_area);

/* storage.c */
t_data		*get_data(void);
t_strat		*get_strat(void);
t_piece		*get_piece(void);
t_tactics	*get_tactics(void);

/* utils.c */
int			clean_exit(t_data *data, const char *str, int error);
t_coord		cell_to_coord(int cell, int board_width);
char		*make_piece_bitmap(t_piece *piece, int board_width);
void		*xalloc(size_t min_size);

/* debug.c */
void		debug_print(char *ptr, int width, int height);
void 		print_valid_moves(t_data *data, t_dintarr *valid_moves);

#endif
