#include "../so_long.h"
#include "../get_next_line.h"

void	stack_bricks_bonus(int x, int y, t_game *g, t_map *map)
{
	int		z;

	z = 50;
	initial_stack_bricks_bonus(x, y, g, map);
	if (map->map[x - 1][y - 1] == 'P')
	{
		mlx_put_image_to_window(g->mlx, g->win, g->hero, y * z - z, x * z - z);
		g->hero_count++;
		map->x_hero = x - 1;
		map->y_hero = y - 1;
	}
	if (map->map[x - 1][y - 1] == '2')
		mlx_put_image_to_window(g->mlx, g->win, g->enemy, \
		 (y - 1.05) * z, (x - 1.1) * z);
	if (map->map[x - 1][y - 1] == 'C')
	{
		mlx_put_image_to_window(g->mlx, g->win, g->coin, y * z - z, x * z - z);
		g->coin_count++;
	}
	if (map->map[x - 1][y - 1] == 'E')
	{
		mlx_put_image_to_window(g->mlx, g->win, g->door, y * z - z, x * z - z);
		g->exit_count++;
	}
}

void	play(t_map *m)
{
	t_game	g;
	int		x;
	int		y;

	g.mlx = mlx_init();
	m->zoom = 50;
	g.win = mlx_new_window(g.mlx, m->zoom * m->width, m->zoom * m->length, "s");
	init_the_game(&g, m->zoom, m->zoom);
	x = m->length;
	y = m->width;
	while (y)
	{
		while (x)
		{
			stack_bricks_bonus(x, y, &g, m);
			x--;
		}
		x = m->length;
		y--;
	}
	g.map = m;
	process_errors(start_heroes(&g));
	mlx_hook(g.win, 2, 1L << 0, key_hook_press, &g);
	mlx_hook(g.win, 17, 1L << 0, key_hook_click, &g);
	mlx_loop(g.mlx);
}

void	read_and_parse(char *line, t_map *map, char **line_common)
{
	char	*tmp;

	map->width = ft_strlen(line);
	if (map->width == 0)
		process_errors(15);
	tmp = *line_common;
	*line_common = ft_strjoin2(*line_common, line);
	if (!(*line_common))
		process_errors(13);
	free(tmp);
	tmp = *line_common;
	*line_common = ft_strjoin2(*line_common, "\n");
	if (!(*line_common))
		process_errors(13);
	free(tmp);
	free(line);
}

void	build_the_map(char *name_of_the_map, t_map *map)
{
	int		error;
	char	*line;
	int		fd;
	char	*line_common;

	fd = open(name_of_the_map, O_RDONLY);
	if (fd == -1)
		process_errors(10);
	map->length = 0;
	line_common = NULL;
	error = check_the_type_of_map(name_of_the_map);
	process_errors(error);
	while (get_next_line(fd, &line))
		read_and_parse(line, map, &line_common);
	free(line);
	map->map = ft_split(line_common, '\n', map);
	if (!(map->map))
		process_errors(13);
	print_mass(map->map);
	free(line_common);
	error = check_borders(map);
	process_errors(error);
}

int	main(int argc, char **argv)
{
	t_map	map;

	if (argc != 2)
		process_errors(12);
	build_the_map(argv[1], &map);
	play(&map);
	free(map.map);
	return (0);
}
