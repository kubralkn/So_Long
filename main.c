#include "so_long.h"

void    game_init(t_game *data)
{
    data->width = 0;
    data->height = 0;
    data->collectables = 0;
    data->exit = 0;
    data->player_x = 0;
    data->player_y = 0;
    data->player = 0;
    data->counter = 0;
}

int main(int ac, char **av)
{
    t_game data;

    if(ac == 2)
    {
        check_file(av[1]);
        game_init(&data);
        map_size(&data, av[1]);
        map_create(&data, av[1]);
        map_wall_check(&data);

        data.mlxstart = mlx_init();
        data.mlxcontinue = mlx_new_window(data.mlxstart, 
                        data.width * RES, data.height * RES, "so_long");
        texture_init(&data);
        data.plyr = data.player_img;
        map_count_pec(&data);
        adding_graphics(&data);
        map_trawel(&data, data.player_y, data.player_x);
        mlx_hook(data.mlxcontinue, 2, 1L << 0, &controls_working, &data);
		mlx_hook(data.mlxcontinue, 17, 1L << 17, (void*) &exit_point, &data);

		mlx_loop(data.mlxstart);

    }
    else
        write(1, "wrong argument", 15);
}