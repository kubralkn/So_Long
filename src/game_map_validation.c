/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_map_validation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalkan <kalkan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:44:21 by kalkan            #+#    #+#             */
/*   Updated: 2025/02/25 15:48:16 by kalkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "../library/Libft/libft.h"
#include <stdlib.h>

void	map_count_pec(t_game *data)
{
	char	location;
	int		index;
	int		x;
	int		y;

	index = 0;
	while (index < data->height * data->width)
	{
		y = index / data->width;
		x = index % data->width;
		location = data->map[y][x];
		if (location == 'E')
			data->exit++;
		else if (location == 'P')
			data->player++;
		else if (location == 'C')
			data->collectables++;
		else if (location != '1' && location != '0' && location != '\n')
			error_msg("Invalid map character!", 0, data);
		index++;
	}
	if (data->player != 1 || data->exit != 1 || data->collectables == 0)
		error_msg("Wrong equipment in map!", 0, data);
}

static char	**map_create_new(t_game *data)
{
	char	**new_map;
	int		i;

	new_map = malloc(sizeof(char *) * (data->height));
	if (!new_map)
		error_msg("Memory allocation failed!", 0, data);
	i = 0;
	while (i < data->height)
	{
		new_map[i] = ft_strdup(data->map[i]);
		if (new_map[i] == NULL)
			break ;
		i++;
	}
	return (new_map);
}

static void	map_flood_fill(char **new_map, int *count, int y, int x)
{
	if (new_map[y][x] == '1')
		return ;
	if (new_map[y][x] == 'C' || new_map[y][x] == 'E')
		(*count)++;
	if (new_map[y][x] == 'E')
	{
		new_map[y][x] = '1';
		return ;
	}
	new_map[y][x] = '1';
	map_flood_fill(new_map, count, y + 1, x);
	map_flood_fill(new_map, count, y - 1, x);
	map_flood_fill(new_map, count, y, x + 1);
	map_flood_fill(new_map, count, y, x - 1);
}

void	map_trawel_free(t_game *data, int y, int x)
{
	char	**new_map;
	int		count;
	int		i;

	count = 0;
	new_map = map_create_new(data);
	map_flood_fill(new_map, &count, y, x);
	if (count != data->collectables + 1)
	{
		i = 0;
		while (i < data->height)
			free(new_map[i++]);
		free(new_map);
		error_msg("Not all collectables are accessible!", 0, data);
	}
	i = 0;
	while (i < data->height)
		free(new_map[i++]);
	free(new_map);
}
