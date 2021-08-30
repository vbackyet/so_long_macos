#include "so_long.h"

static void	key_move_step(t_game *game, int x_hero, int y_hero, \
							t_map *m)
{
	if (game->map->map[x_hero][y_hero] == '1')
		return ;
	if (game->map->map[x_hero][y_hero] == 'C')
		game->coin_count--;
	if (game->map->map[x_hero][y_hero] == 'E')
	{			
		if (game->coin_count == 0)
			exit(1);
		else
			return ;
	}
	if (game->map->map[x_hero][y_hero] == '2')
	{
		game->counter++;
		printf("Вы погибли:(((\n");
		exit(1);
	}
	game->counter++;
	mlx_put_image_to_window(game->mlx, game->win, \
	game->floor, m->y_hero * m->zoom, m->x_hero * m->zoom);
	mlx_put_image_to_window(game->mlx, game->win, \
	game->hero, y_hero * game->map->zoom, x_hero * game->map->zoom);
	game->map->x_hero = x_hero;
	game->map->y_hero = y_hero;
	printf("Количество шагов: %d\n", game->counter);
}

int	key_hook_press(int keycode, t_game *g)
{
	if (keycode == 13)
		key_move_step(g, g->map->x_hero - 1, g->map->y_hero, g->map);
	if (keycode == 2)
		key_move_step(g, g->map->x_hero, g->map->y_hero + 1, g->map);
	if (keycode == 1)
		key_move_step(g, g->map->x_hero + 1, g->map->y_hero, g->map);
	if (keycode == 0)
		key_move_step(g, g->map->x_hero, g->map->y_hero - 1, g->map);
	if (keycode == 53)
	{
		mlx_destroy_window(g->mlx, g->win);
		exit(1);
	}
	return (1);
}

int	key_hook_click(int keycode, t_game *game)
{
	exit(1);
}

void	process_errors_cont(int error)
{
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
	if (error == 13)
		printf("Ошибка маллока\n");
	if (error == 14)
		printf("Количество героев превышает 1\n");
	if (error == 15)
		printf("Пустая строка по в карте\n");
	if (error == 16)
		printf("Буковка не подходит\n");
}

void	process_errors(int error)
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
		else
			process_errors_cont(error);
		exit(0);
	}
}
