/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpolonen <tpolonen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 19:16:22 by tpolonen          #+#    #+#             */
/*   Updated: 2022/10/01 20:48:13 by tpolonen         ###   ########.fr       */
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

typedef struct s_gamedata
{
	char	player;
	int		width;
	int		height;
	void	*oboard_ptr;
	void	*xboard_ptr;
}	t_data;

#endif
