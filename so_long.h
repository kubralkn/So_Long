#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include "./library/Ft_Printf/ft_printf.h"
# include "./library/Libft/libft.h"
# include "./library/GetNextLine/get_next_line.h"
# include "./library/minilibx-linux/mlx.h"

# define RES 64
# define W 119
# define A 97
# define S 115
# define D 100
# define ESC 65307

typedef struct s_game
{
    char    **map;
    int     width;
    int     height;
    void    *mlxstart;
    void    *mlxcontinue;
    int     collectables;
    int     exit;
    int     player;
    int     player_x;
    int     player_y;
    int     counter;
    void    *plyr;
    void    *player_img;
    void    *coin_img;
    void    *exit_img;
    void    *wall_img;
    void    *background_img;
}   t_game;

void    error_msg(char *str);
void    check_file(char *str);
void    map_size(t_game *data, char *map_name);
void	map_create(t_game *data, char *str);
void	map_wall_check(t_game *data);
void	map_count_pec(t_game *data);
int     controls_working(int key, t_game *data);
void    exit_point(void *data);
void	adding_graphics(t_game *data);
void    texture_init(t_game *data);
void	map_trawel(t_game *data, int y, int x);
void	map_count_pec(t_game *data);
void	place_player(t_game *data, int width, int height);


#endif
