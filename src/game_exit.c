/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalkan <kalkan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:45:25 by kalkan            #+#    #+#             */
/*   Updated: 2025/02/19 13:43:42 by kalkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "../library/GetNextLine/get_next_line.h"
#include "../library/Ft_Printf/ft_printf.h"
#include "../library/minilibx-linux/mlx.h"
#include <stddef.h>

void	error_msg(char *str, int check, void *data)
{
	if (check == 1)
	{
		ft_printf("Error \n%s\n", str);
		exit(1);
	}
	else if (check == 3)
	{
		ft_printf("\n%s\n", str);
		game_exit((t_game *)data);
	}
	else
	{
		ft_printf("Error \n%s\n", str);
		game_exit((t_game *)data);
	}
}

static void	mlx_images_free(t_game *data)
{
	if (data && data->player_img)
	{
		mlx_destroy_image(data->mlxstart, data->player_img);
		data->player_img = NULL;
	}
	if (data && data->coin_img)
	{
		mlx_destroy_image(data->mlxstart, data->coin_img);
		data->coin_img = NULL;
	}
	if (data && data->exit_img)
	{
		mlx_destroy_image(data->mlxstart, data->exit_img);
		data->exit_img = NULL;
	}
	if (data && data->wall_img)
	{
		mlx_destroy_image(data->mlxstart, data->wall_img);
		data->wall_img = NULL;
	}
}

static void	free_map(t_game *data)
{
	int	line;

	line = 0;
	if (data && data->map)
	{
		while (line < data->height)
		{
			if (data->map[line] != NULL)
			{
				free(data->map[line]);
				data->map[line] = NULL;
			}
			line++;
		}
		free(data->map);
		data->map = NULL;
	}
}

static void	free_mlx(t_game *data)
{
	if (data)
		mlx_images_free(data);
	if (data && data->mlxstart)
	{
		if (data->mlxcontinue)
		{
			mlx_clear_window(data->mlxstart, data->mlxcontinue);
			mlx_destroy_window(data->mlxstart, data->mlxcontinue);
			data->mlxcontinue = NULL;
		}
		mlx_destroy_display(data->mlxstart);
		free(data->mlxstart);
		data->mlxstart = NULL;
	}
}

int	game_exit(t_game *data)
{
	free_map(data);
	free_mlx(data);
	exit(0);
}
