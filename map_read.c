#include "so_long.h"

static int map_skip_space(char *str)
{
    int i;

    i = 0;
    while (str[i] <= 32)
    {
        return (0);
    } 
    return (1);
}

void    map_size(t_game *data, char *map_name)
{
    char    *line;
    int     fd;
    int     flag;

    if ((fd = open(map_name, O_RDONLY)) < 0)
        error_msg("Failed to open map file!");
    flag = 1;
    while ((line = get_next_line(fd)) != NULL)
    {
        if(map_skip_space(line) == 1)
        {
            if(flag == 1)
            {
                data->width = ft_strlen(line) - 1;
                flag = 0;
            }
            data->height++;
        }
        free(line);
    }
    close(fd);
}

static void    map_line_control(char *line, t_game *data)
{
    int i;

    i = 0;
    while (line[i] && line[i] != '\n')
    {
        if (line[i] != '1' && line[i] != '0' && line[i] != 'P' && line[i] != 'E' && line[i] != 'C')
        {
            free(line);
            error_msg("Invalid map: invalid characters in map");
        }
        i++;
    }
    if (i != data->width)
    {
        free(line);
        error_msg("Invalid map: map lines are not of equal length");
    }
}
void	map_create(t_game *data, char *str)
{
	int		fd;
	int		i;
	char	*line;

	data->map = malloc(sizeof(char *) * data->height);
	if (!data->map)
		error_msg("Memory allocation failed");
	fd = open(str, O_RDONLY);
	if (fd < 0)
		error_msg("Failed to open map file");
	i = 0;
	while (i < data->height)
	{
		if (!(line = get_next_line(fd)))
			error_msg("Failed to read line from map file");
		if (map_skip_space(line))
		{
			map_line_control(line, data);
			if (!(data->map[i] = ft_strdup(line)))
				error_msg("Memory allocation failed");
			i++;
		}
		free(line);
	}
	close(fd);
}

void	map_wall_check(t_game *data)
{
 	int	i;
 	int	w;
 	int	h;

 	i = 0;
 	w = data->width - 1;
 	h = data->height - 1;
 	while (i <= h)
 	{
 		if (data->map[i][0] != '1' || data->map[i][w] != '1')
 			error_msg("Invalid map: walls not properly set");
         i++;
 	}
    i = 0;
 	while (i <= w)
 	{
 		if (data->map[0][i] != '1' || data->map[h][i] != '1')
 		    error_msg("Invalid map: walls not properly set");
        i++;
 	}
}
