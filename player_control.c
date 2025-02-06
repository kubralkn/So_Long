#include "so_long.h"

static int	move_control(t_game *data, int i, int j)
{
    if (data->map[i][j] == 'E')
    {
        if (data->collectables != 0)
			return (0);
        ft_printf("YOU WIN\n");
        exit_point((void *)data);
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

static int	move_in_direction(t_game *data, int direction_x, int direction_y)
{
    int new_y;
    int new_x;

    new_y = data->player_y + direction_y;
    new_x = data->player_x + direction_x;
    if (new_x < 0 || new_y < 0 || new_x >= data->width || new_y >= data->height)
        return (0);
    if (data->map[new_y][new_x] == '1')
        return (0);
    if (!move_control(data, new_y, new_x))
        return (0);
    data->player_y = new_y;
    data->player_x = new_x;
    return (1);
}

static int	key_movement(t_game *data, int movement)
{
    if (movement == W)
        return (move_in_direction(data, 0, -1));
    else if (movement == S)
        return (move_in_direction(data, 0, 1));
    else if (movement == A)
        return (move_in_direction(data, -1, 0));
    else if (movement == D)
        return (move_in_direction(data, 1, 0));
    return (0);
}

int controls_working(int key, t_game *data)
{
    int result;

    result = 0;
    if (key == ESC)
        exit_point((void *)data);
    result = key_movement(data, key);
    if (result)
    {
        ft_printf("Step Count: %d\n", data->counter);
        ft_printf("Left Coins: %d\n", data->collectables);
        adding_graphics(data);
    }
    return (1);
}

void    exit_point(void *data)
{
    (void)data;
    exit(0);
}