/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalkan <kalkan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:00:41 by kalkan            #+#    #+#             */
/*   Updated: 2025/02/19 13:43:33 by kalkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define RES 64
# define W 119
# define A 97
# define S 115
# define D 100
# define ESC 65307

typedef struct s_game
{
	char	**map;

	int		width;
	int		height;
	int		collectables;
	int		exit;
	int		player;
	int		player_x;
	int		player_y;
	int		counter;

	void	*mlxstart;
	void	*mlxcontinue;
	void	*player_img;
	void	*coin_img;
	void	*exit_img;
	void	*wall_img;
}	t_game;

int		game_exit(t_game *data);
int		map_tracking(int key, t_game *data);
void	map_create(t_game *data, char *str);
void	map_size(t_game *data, char *map_name);
void	map_wall_check(t_game *data);
void	map_count_pec(t_game *data);
void	map_trawel_free(t_game *data, int y, int x);
void	map_count_pec(t_game *data);
void	error_msg(char *str, int check, void *data);
void	game_adding_graphics(t_game *data);
void	game_texture_init(t_game *data);

#endif
