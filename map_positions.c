/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_positions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalkan <kalkan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:10:19 by kalkan            #+#    #+#             */
/*   Updated: 2025/02/04 17:43:39 by kalkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_count_pec(t_game *data)
{
	int	i;
	int	j;

	i = -1;
	data->player = 0;
	data->exit = 0;
	data->collectables = 0;
	while (++i < data->height)
	{
		j = -1;
		while (data->map[i][++j])
		{
			if (data->map[i][j] == 'E')
				data->exit++;
			else if (data->map[i][j] == 'P')
				data->player++;
			else if (data->map[i][j] == 'C')
				data->collectables++;
			else if (data->map[i][j] != '1'
					&& data->map[i][j] != '0'
					&& data->map[i][j] != '\n')
					error_msg("Unknown value on the map");
		}
	}
	if (data->player != 1 || data->exit != 1 || data->collectables == 0)
		error_msg("Wrong map entry");
}

static char	**map_create_new(t_game *data)
{
	char	**new_map;
	int		i;

	new_map = malloc(sizeof(char *) * (data->height));
	if (!new_map)
	{
		error_msg("Place could not be reserved");
		//exit_point((void *)data);
	}
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
	if (y < 0 || x < 0)
        return ;
	if (new_map[y][x] == '1')
		return ;
	if (new_map[y][x] == 'C' || new_map[y][x] == 'E')
		(*count)++;
	new_map[y][x] = '1';
	map_flood_fill(new_map, count, y + 1, x);
	map_flood_fill(new_map, count, y - 1, x);
	map_flood_fill(new_map, count, y, x + 1);
	map_flood_fill(new_map, count, y, x - 1);
}

static void	map_free(char **new_map, t_game *data)
{
	int	i;

	i = 0;
	while (i < data->height)
	{
		free(new_map[i]);
		i++;
	}
	free(new_map);
}

void	map_trawel(t_game *data, int y, int x)
{
	char	**new_map;
	int		count;

	count = 0;
	new_map = map_create_new(data);
	map_flood_fill(new_map, &count, y, x);
	if (count != data->collectables + 1)
	{
		map_free(new_map, data);
		error_msg("Wrong Map");
		//exit_point((void *)data);
	}
	map_free(new_map, data);
}
