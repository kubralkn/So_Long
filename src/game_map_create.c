/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_map_create.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalkan <kalkan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:44:42 by kalkan            #+#    #+#             */
/*   Updated: 2025/02/19 13:40:18 by kalkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "../library/GetNextLine/get_next_line.h"
#include "../library/Libft/libft.h"
#include <fcntl.h>
#include <stddef.h>

void	map_size(t_game *data, char *map_name)
{
	char	*line;
	int		fd;
	int		flag;

	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		error_msg("Map file error!", 0, data);
	flag = 1;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (flag == 1)
			data->width = ft_strlen(line) - 1;
		data->height++;
		free(line);
		line = get_next_line(fd);
		if (flag == 1)
			flag = 0;
	}
	if (data->height == 0)
	{
		close(fd);
		error_msg("Map file is empty!", 0, data);
	}
	close(fd);
}

static void	map_line_control(char *line, t_game *data)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != 'P'
			&& line[i] != 'E' && line[i] != 'C')
		{
			free(line);
			error_msg("Invalid characters in map!", 0, data);
		}
		i++;
	}
	if (i != data->width)
	{
		free(line);
		error_msg("Map lines are not of equal length!", 0, data);
	}
	line = NULL;
}

static void	init_map(t_game *data)
{
	int	i;

	data->map = malloc(sizeof(char *) * data->height);
	if (!(data->map))
		error_msg("Memory allocation failed!", 0, data);
	i = -1;
	while (++i < data->height)
		data->map[i] = NULL;
}

void	map_create(t_game *data, char *str)
{
	int		fd;
	int		i;
	char	*line;

	init_map(data);
	fd = open(str, O_RDONLY);
	if (fd < 0)
		error_msg("Failed to open mapfile!", 0, data);
	i = -1;
	while (++i < data->height)
	{
		line = get_next_line(fd);
		if (!line)
			error_msg("Failed to read line from mapfile!", 0, data);
		map_line_control(line, data);
		data->map[i] = ft_strdup(line);
		if (!(data->map[i]))
		{
			free(line);
			error_msg("Memory allocation failed!", 0, data);
		}
		free(line);
	}
	close(fd);
}

void	map_wall_check(t_game *data)
{
	int	i;
	int	w;
	int	h;

	i = 0;
	w = data->width - 1;
	h = data->height - 1;
	while (i <= h)
	{
		if (data->map[i][0] != '1' || data->map[i][w] != '1')
			error_msg("Invalid map: walls not properly set!", 0, data);
		i++;
	}
	i = 0;
	while (i <= w)
	{
		if (data->map[0][i] != '1' || data->map[h][i] != '1')
			error_msg("Invalid map: walls not properly set!", 0, data);
		i++;
	}
}
