#include "so_long.h"

void	initial_stack_bricks(int x, int y, t_game *g, t_map *map)
{
	int		z;

	z = 50;
	if (map->map[x - 1][y - 1] == '1')
		mlx_put_image_to_window(g->mlx, g->win, g->wall, y * z - z, x * z - z);
	else if (map->map[x - 1][y - 1] == '0')
		mlx_put_image_to_window(g->mlx, g->win, g->floor, y * z - z, x * z - z);
	else if (!(ft_contains("102PCE", map->map[x - 1][y - 1])))
		process_errors(16);
	else
		mlx_put_image_to_window(g->mlx, g->win, g->floor, y * z - z, x * z - z);
}

void	init_the_game(t_game *g, int width, int length)
{
	g->coin_count = 0;
	g->counter = 0;
	g->exit_count = 0;
	g->hero_count = 0;
	g->wall = mlx_xpm_file_to_image(g->mlx, "wall.xpm", &width, &length);
	g->door = mlx_xpm_file_to_image(g->mlx, "door.xpm", &width, &length);
	g->goblin = mlx_xpm_file_to_image(g->mlx, "goblin.xpm", &width, &length);
	g->floor = mlx_xpm_file_to_image(g->mlx, "floor.xpm", &width, &length);
	g->hero = mlx_xpm_file_to_image(g->mlx, "nevsk7.xpm", &width, &length);
	g->coin = mlx_xpm_file_to_image(g->mlx, "chiken.xpm", &width, &length);
	g->enemy = mlx_xpm_file_to_image(g->mlx, "7.xpm", &width, &length);
}

int	check_the_type_of_map(char *name_of_the_map)
{
	int	len_of_the_word;

	len_of_the_word = ft_strlen(name_of_the_map);
	if (name_of_the_map[len_of_the_word - 1] == 'r' && \
			name_of_the_map[len_of_the_word - 2] == 'e' && \
	 			name_of_the_map[len_of_the_word - 3] == 'b' && \
				 name_of_the_map[len_of_the_word - 4] == '.')
		return (0);
	return (1);
}

int	check_borders(t_map *map)
{
	int		i;
	int		len;

	i = 0;
	len = map->length;
	while (map->map[i] != NULL)
	{
		if (ft_strlen(map->map[i]) != map->width)
			return (2);
		if (map->map[i][0] != '1')
			return (3);
		if (map->map[i][map->width - 1] != '1')
			return (4);
		i++;
	}
	if (ft_consist(map->map[0], '1'))
		return (5);
	if (ft_consist(map->map[len - 1], '1'))
		return (6);
	return (0);
}

int	start_heroes(t_game *game)
{
	if (game->hero_count == 0)
		return (7);
	if (game->exit_count == 0)
		return (8);
	if (game->coin_count == 0)
		return (9);
	if (game->hero_count > 1)
		return (14);
	return (0);
}
