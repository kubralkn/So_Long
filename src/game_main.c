/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalkan <kalkan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:44:47 by kalkan            #+#    #+#             */
/*   Updated: 2025/02/19 15:27:50 by kalkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "../library/Libft/libft.h"
#include "../library/minilibx-linux/mlx.h"
#include <fcntl.h>
#include <stddef.h>
#include <unistd.h>

static void	game_init(t_game *data)
{
	data->width = 0;
	data->height = 0;
	data->collectables = 0;
	data->exit = 0;
	data->player_x = 0;
	data->player_y = 0;
	data->player = 0;
	data->counter = 0;
	data->map = NULL;
	data->player_img = NULL;
	data->coin_img = NULL;
	data->exit_img = NULL;
	data->wall_img = NULL;
	data->mlxstart = NULL;
	data->mlxcontinue = NULL;
}

static void	game_check_file(char *str)
{
	int	len;
	int	fd;

	len = ft_strlen(str);
	if (!(str[len - 1] == 'r' && str[len - 2] == 'e'
			&& str[len - 3] == 'b' && str[len - 4] == '.')
		|| !(ft_isprint(str[len - 5])))
		error_msg("Invalid filename extension", 1, NULL);
	fd = open(str, O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		error_msg("Could not open map file", 1, NULL);
	}
	close(fd);
}

static void	game_all_function(t_game *data, char *map_path)
{
	game_init(data);
	game_check_file(map_path);
	map_size(data, map_path);
	map_create(data, map_path);
	map_wall_check(data);
	data->mlxstart = mlx_init();
	if (!data->mlxstart)
		error_msg("MLX initialization failed", 0, data);
	data->mlxcontinue = mlx_new_window(data->mlxstart,
			data->width * RES, data->height * RES, "so_long");
	if (!data->mlxcontinue)
		error_msg("Failed to create MLX window", 0, data);
	game_texture_init(data);
	map_count_pec(data);
	game_adding_graphics(data);
	map_trawel_free(data, data->player_y, data->player_x);
}

static void	setup_hooks(t_game *data)
{
	mlx_key_hook(data->mlxcontinue, &map_tracking, data);
	mlx_hook(data->mlxcontinue, 17, 0, (void *) &game_exit, data);
}

int	main(int ac, char **av)
{
	t_game	data;

	if (ac == 2)
	{
		game_all_function(&data, av[1]);
		setup_hooks(&data);
		mlx_loop(data.mlxstart);
	}
	else
		error_msg("Error: Wrong number of arguments", 1, NULL);
	return (0);
}
