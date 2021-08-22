#include "so_long.h"
#include "get_next_line.h"

 void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

 void process_errors(int error)
{
	if (error)
	{
		printf("Error:\n");
		if (error == 1)
			printf("Формат не соотвестует .ber\n");
		if (error == 2)
			printf("Ширина не везде одинаковая\n");
		if (error == 3)
			printf("Левая стенка не закрыта\n");
		if (error == 4)
			printf("Правая стенка не закрыта\n");
		if (error == 5)
			printf("Верхняя стенка не закрыта\n");
		if (error == 6)
			printf("Нижняя стенка не закрыта\n");
		if (error == 7)
			printf("Не хватает героя\n");
		if (error == 8)
			printf("Не хватает выхода\n");
		if (error == 9)
			printf("Не хватает монеток\n");
		if (error == 10)
			printf("Файл не прочитался\n");
		if (error == 11)
			printf("Ошибка маллока\n");
		if (error == 12)
			printf("Недостаточно аргументов\n");
		exit(0);
	}
}


static void	key_move_step(t_game *game, int x_hero, int y_hero , int x_wall, int y_wall)
{
	if (game->map->map[x_hero][y_hero] == '1')
		return;
	if (game->map->map[x_hero][y_hero] == 'C')
		game->coin_count--;
	if (game->map->map[x_hero][y_hero] == 'E')
	{
		if (game->coin_count == 0)
		{					
			game->counter++;
			exit(1);
		}
		else
			return;
	}
	game->counter++;
	mlx_put_image_to_window(game->mlx, game->win, \
	game->floor, y_wall * game->map->zoom, \
	x_wall* game->map->zoom);
	mlx_put_image_to_window(game->mlx, game->win, \
	game->hero, y_hero* game->map->zoom, \
	x_hero* game->map->zoom);
		// printf("(%d - %d)hero -(%d, %d) wall\n", x_hero, y_hero , x_wall, y_wall);
	game->map->x_hero =x_hero;
	game->map->y_hero =y_hero;
	printf("Количество шагов: %d\n", game->counter);
}



int	key_hook_press(int keycode, t_game *game)
{
	printf("%d - keyhook\n", keycode);
	if (keycode == 13)	
		key_move_step(game, game->map->x_hero - 1 , game->map->y_hero, game->map->x_hero , game->map->y_hero);
	if (keycode == 2)	
		key_move_step(game, game->map->x_hero , game->map->y_hero + 1, game->map->x_hero , game->map->y_hero);
	if (keycode == 1)	
		key_move_step(game, game->map->x_hero + 1 , game->map->y_hero, game->map->x_hero , game->map->y_hero);
	if (keycode == 0)	
		key_move_step(game, game->map->x_hero , game->map->y_hero - 1, game->map->x_hero , game->map->y_hero);
	if (keycode == 53)
		mlx_destroy_window(game->mlx, game->win);
	return (1);
}

int	key_hook_click(int keycode, t_game *game)
{
	exit(1);
}

int start_heroes(t_game *game)
{
	if (game->hero_count == 0)
		return(7);
	if (game->exit_count == 0)
		return(8);
	if (game->coin_count == 0)
		return(9);
	return(0);
}


void init_the_game(t_game *game, int width, int length)
{
	game->coin_count = 0;
	game->counter = 0;
	game->exit_count = 0;
	game->hero_count = 0;
	game->wall = mlx_xpm_file_to_image(game->mlx, "wall.xpm", &width, &length);
	game->door = mlx_xpm_file_to_image(game->mlx, "door.xpm", &width, &length);
	game->goblin = mlx_xpm_file_to_image(game->mlx, "goblin.xpm", &width, &length);
	game->floor = mlx_xpm_file_to_image(game->mlx, "floor.xpm", &width, &length);
	game->hero = mlx_xpm_file_to_image(game->mlx, "nevsk.xpm", &width, &length);
	game->coin = mlx_xpm_file_to_image(game->mlx, "chiken.xpm", &width, &length);
}


int	play(t_map *map)
{
	// t_data	img;
	t_game game;

	game.mlx = mlx_init();

	int zoom = 50;
	int x =zoom * map->length;
	int y= zoom * map->width;
	//1 - ширина 2 - высота
	game.win = mlx_new_window(game.mlx, y, x, "so_long");
	int width = zoom;
	int length = zoom;
	init_the_game(&game, width, length);
	x = x/zoom;
	y = y/zoom;
	while (y)
	{
		while (x)
		{
			// printf("%d\n", map->map[x-1][y-1]);
			if (map->map[x-1][y-1] == '1')
				mlx_put_image_to_window(game.mlx, game.win , game.wall, y*zoom - zoom , x*zoom - zoom);
			else if (map->map[x-1][y-1] == '0')
				mlx_put_image_to_window(game.mlx, game.win , game.floor, y*zoom - zoom , x*zoom - zoom);
			else{
			mlx_put_image_to_window(game.mlx, game.win , game.floor, y*zoom - zoom , x*zoom - zoom);	
			if (map->map[x-1][y-1] == 'P')
			{
				mlx_put_image_to_window(game.mlx, game.win , game.hero, y*zoom - zoom , x*zoom - zoom);
				game.hero_count++;
				map->x_hero = x-1;
				map->y_hero = y-1;
			}
			if (map->map[x-1][y-1] == 'C')
			{
				mlx_put_image_to_window(game.mlx, game.win , game.coin, y*zoom - zoom , x*zoom - zoom);
				game.coin_count++;
			}
			if (map->map[x-1][y-1] == 'E')
			{
				mlx_put_image_to_window(game.mlx, game.win , game.door, y*zoom - zoom , x*zoom - zoom);
				game.exit_count++;
			}
			}
			x--;
		}
		x = map->length;
		y--;
	}
	map->zoom = zoom;
	game.map = map;
	int error = start_heroes(&game);
	if (error)
		process_errors(error);
	mlx_hook(game.win, 2, 1L<<0, key_hook_press, &game);
	mlx_hook(game.win, 17, 1L<<0, key_hook_click, &game);
	// pri/ntf("HEEEEKKOOOOOOOOOOOOOO3");
	mlx_loop(game.mlx);
	return(0);
}





// int	ft_strlen(const char *s)
// {
// 	int length;

// 	if (s == NULL)
// 		return (0);
// 	length = 0;
// 	while (s[length])
// 		length++;
// 	return (length);
// }



int check_the_type_of_map(char *name_of_the_map)
{
	int len_of_the_word = ft_strlen(name_of_the_map);
	if (name_of_the_map[len_of_the_word-1] == 'r' && name_of_the_map[len_of_the_word-2] == 'e' &&\
	 			name_of_the_map[len_of_the_word-3] == 'b' && name_of_the_map[len_of_the_word-4] == '.')
		return (0);
	return(1);
}


/////////***************************************
// char	*ft_strchr(const char *s, int c)
// {
// 	int i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == c)
// 			return ((char *)s + i);
// 		i++;
// 	}
// 	if (s[i] == c)
// 		return ((char *)s + i);
// 	return (0);
// }




///// ******************************************


int ft_consist(char *the_word , char the_symbol)
{
	int i = 0;
	while (the_word[i] != '\0')
	{
		if (the_word[i] != the_symbol)
			return(1);
		i++;
	}
	return(0);
}


int check_borders(t_map *map)
{
	int i;
	i = 0;
	int len = map->length;
	while (map->map[i] != NULL)
	{
		if (ft_strlen(map->map[i]) !=  map->width)
			return(2);
		if (map->map[i][0] != '1')
			return(3);
		if (map->map[i][map->width - 1] != '1')
			return(4);
		i++;
		//printf("%d - %swidth_proverka\n", ft_strlen(map->map[i]), map->map[i]);
	}
	if (ft_consist(map->map[0], '1'))
		return(5);
	if (ft_consist(map->map[len-1], '1'))
		return(6);
	return 0;
}





void build_the_map(char *name_of_the_map, t_map *map)
{
	int error;
	error  = check_the_type_of_map(name_of_the_map);
	char *line;
	char *tmp;
	int fd = open(name_of_the_map, O_RDONLY);
	if (fd == -1)
		error = 10;
	process_errors(error);
	map->length = 0;
	char *line_common = NULL;
	while (get_next_line(fd, &line))
	{
		map->width = ft_strlen(line);
		// printf("%d - width\n", map->width);
		// printf("{%d}\n" ,map->width);
		tmp = line_common;
		line_common = ft_strjoin2(line_common, line);
		free(tmp);
		// printf("{%s}\n" ,line_common);
		tmp = line_common;
		line_common = ft_strjoin2(line_common, "\n");
		free(tmp);
		free(line);
	}
	free(line);
	// printf("{%s}\n" ,line_common);
	map->map = ft_split(line_common, '\n', map);
	free(line_common);
	error = check_borders(map);
	process_errors(error);
}



int main(int argc, char **argv)
{
	t_map map;

	if (argc != 2)
		process_errors(12);

	build_the_map(argv[1], &map);
	sleep(100);
	//play(&map);
	free(map.map);
	return (0);
}

