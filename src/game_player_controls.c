/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_player_controls.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalkan <kalkan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:44:29 by kalkan            #+#    #+#             */
/*   Updated: 2025/02/20 11:38:08 by kalkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "../library/Ft_Printf/ft_printf.h"

static int	player_move_control(t_game *data, int i, int j)
{
	if (data->map[i][j] == 'E')
	{
		if (data->collectables != 0)
			return (0);
		error_msg("YOU WIN!\n", 3, data);
	}
	if (data->map[i][j] == 'C')
		data->collectables--;
	data->map[data->player_y][data->player_x] = '0';
	data->map[i][j] = 'P';
	data->player_y = i;
	data->player_x = j;
	data->counter++;
	return (1);
}

static int	player_movement(t_game *data, int direction_x, int direction_y)
{
	int	new_y;
	int	new_x;

	new_y = data->player_y + direction_y;
	new_x = data->player_x + direction_x;
	if (new_x < 0 || new_y < 0 || new_x >= data->width || new_y >= data->height)
		return (0);
	if (data->map[new_y][new_x] == '1')
		return (0);
	return (player_move_control(data, new_y, new_x));
}

static int	game_key_movement(t_game *data, int movement)
{
	if (movement == W)
		return (player_movement(data, 0, -1));
	else if (movement == S)
		return (player_movement(data, 0, 1));
	else if (movement == A)
		return (player_movement(data, -1, 0));
	else if (movement == D)
		return (player_movement(data, 1, 0));
	return (0);
}

int	map_tracking(int key, t_game *data)
{
	int	result;

	result = 0;
	if (key == ESC)
		game_exit(data);
	result = game_key_movement(data, key);
	if (result)
	{
		ft_printf("Step Count: %d\n", data->counter);
		ft_printf("Left Coins: %d\n", data->collectables);
		game_adding_graphics(data);
	}
	return (1);
}
