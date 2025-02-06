#include "so_long.h"

void *texture_in_image(t_game *data, char *path)
{
    int x;
    int y;
    void *image;

    image = mlx_xpm_file_to_image(data->mlxstart, path, &x, &y);
    if (!image)
    {
        exit(0);
        //free
    }
    return (image);
}
void    texture_init(t_game *data)
{
    data->coin_img = texture_in_image(data, "./img/coin.xpm");
    data->wall_img = texture_in_image(data, "./img/wall.xpm");
    data->player_img = texture_in_image(data, "./img/player.xpm");
    data->exit_img = texture_in_image(data, "./img/exit.xpm");
    data->background_img = texture_in_image(data, "./img/background.xpm");
}


void	place_player(t_game *data, int width, int height)
{
	mlx_put_image_to_window(data->mlxstart,
		data->mlxcontinue, data->player_img, width * RES, height * RES);
	data->player_x = width;
	data->player_y = height;
}
void	adding_graphics(t_game *data)
{
	int	height;
	int	width;

	height = -1;
	mlx_clear_window(data->mlxstart, data->mlxcontinue);
	while (++height < data->height)
	{
		width = -1;
		while (data->map[height][++width])
		{
			mlx_put_image_to_window(data->mlxstart,
					data->mlxcontinue, data->background_img, width * RES, height * RES);
			if (data->map[height][width] == '1')
				mlx_put_image_to_window(data->mlxstart,
					data->mlxcontinue, data->wall_img, width * RES, height * RES);
			else if (data->map[height][width] == 'C')
				mlx_put_image_to_window(data->mlxstart, data->mlxcontinue,
					data->coin_img, width * RES, height * RES);
			else if (data->map[height][width] == 'P')
				place_player(data, width, height);
			else if (data->map[height][width] == 'E')
				mlx_put_image_to_window(data->mlxstart,
					data->mlxcontinue, data->exit_img, width * RES, height * RES);
		}
	}
}
