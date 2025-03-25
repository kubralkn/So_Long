/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_graphics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalkan <kalkan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:45:18 by kalkan            #+#    #+#             */
/*   Updated: 2025/02/21 12:11:13 by kalkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "../library/minilibx-linux/mlx.h"
#include <stdlib.h>

static void	*texture_in_image(t_game *data, char *path)
{
	int		x;
	int		y;
	void	*image;

	image = mlx_xpm_file_to_image(data->mlxstart, path, &x, &y);
	if (!image)
		error_msg("Image failed", 0, data);
	return (image);
}

void	game_texture_init(t_game *data)
{
	data->coin_img = texture_in_image(data, "./textures/coin.xpm");
	data->wall_img = texture_in_image(data, "./textures/wall.xpm");
	data->player_img = texture_in_image(data, "./textures/player.xpm");
	data->exit_img = texture_in_image(data, "./textures/exit.xpm");
}

static void	render_image(t_game *data, char location, int x, int y)
{
	void	*img;

	img = NULL;
	if (location == '1')
		img = data->wall_img;
	else if (location == 'C')
		img = data->coin_img;
	else if (location == 'P')
	{
		data->player_x = x;
		data->player_y = y;
		img = data->player_img;
	}
	else if (location == 'E')
		img = data->exit_img;
	if (img)
		mlx_put_image_to_window(data->mlxstart, data->mlxcontinue,
			img, x * RES, y * RES);
}

void	game_adding_graphics(t_game *data)
{
	int	index;
	int	x;
	int	y;

	index = 0;
	mlx_clear_window(data->mlxstart, data->mlxcontinue);
	while (index < data->height * data->width)
	{
		y = index / data->width;
		x = index % data->width;
		render_image(data, data->map[y][x], x, y);
		index++;
	}
}
