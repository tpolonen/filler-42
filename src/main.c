/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpolonen <tpolonen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 19:16:16 by tpolonen          #+#    #+#             */
/*   Updated: 2022/10/05 19:30:44 by tpolonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int set_player(t_data *data, char *header)
{
	if (!header)
		return (2);
	if (ft_strncmp(header, "$$$ exec p", 10) != 0)
		return (3);
	if (ft_strstr(header, "tpolonen.filler") == NULL)
		return (4);
	if (ft_strstr(header, "p1") != NULL)
		data->player = 'o';
	else
		data->player = 'x';
	free(header);
	return (data->player == 0);
}

static int init_data(t_data *data, char *header)
{
	char	*seek;

	if (!header)
		return (2);
	if (ft_strncmp(header, "Plateau ", 8) != 0)
		return (5);
	if (ft_strchr(header, ':') == NULL)
		return (6);
	seek = header + 8;
	data->width = (int)ft_strtol(seek, &seek);
	data->height = (int)ft_strtol(seek, &seek);
	data->oboard_ptr = xalloc(data->width * data->height);
	data->xboard_ptr = xalloc(data->width * data->height);
	if (data->oboard_ptr == NULL || data->xboard_ptr == NULL)
		return (7);
	return ((data->width == 0) || (data->height == 0));
}

int main(void)
{
	static t_data	data;
	char			*next;
	FILE			*debug;
	int				error;
	int				bytes;

	debug = fopen(".last", "w");

	ft_getline(0, &next);
	error = set_player(&data, next);
	if (error)
		return (clean_exit(&data, "Error in player data: ", error));
	ft_getline(0, &next);
	error = init_data(&data, next);
	if (error)
		return (clean_exit(&data, "Error in map header: ", error));
	// game loop until opponent dies or moves run out
	bytes = ft_getline(0, &next);
	fprintf(debug, "%d\t", bytes);
	while (bytes > 0)
	{
		fprintf(debug, "%s\n", next);
		fflush(debug);
		if (next)
			free(next);
		bytes = ft_getline(0, &next);
		fprintf(debug, "%d\t", bytes);
	}
	fprintf(debug, "END\n");
	fflush(debug);
	// suicide
	fclose(debug);
	return (clean_exit(&data, "-42 -42", 0));
}
