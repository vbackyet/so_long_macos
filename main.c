#include "so_long.h"
#include "get_next_line.h"
#include <mlx.h>
#include <stdio.h>
#include  <unistd.h>




typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


typedef struct s_map{
	char 	**map;
	int 	length;
	int 	width;
	int x_hero;
	int y_hero;
	int zoom;

}				t_map;



typedef struct	s_game{
	void *mlx;
	void *win;
	void *wall;
	void *goblin;
	void *door;
	void *floor;
	void *hero;
	void *coin;
	int coin_count;
	int counter;
	t_map *map;

}				t_game;
 
int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (i); 
	while (str[i])
	{
		i++;
	}
	return (i);
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


// int	key_hook(int keycode, t_game *vars)
// {
// 	// printf("HEEEEKKOOOOOOOOOOOOOO");
// 	printf("%d - keycode\n",keycode );
// 	// key_move_step(vars, 55*10, 55*12);
// 	return (1);
// }
// wdsa - 13 2 1 0
int	play(t_map *map)
{
	// t_data	img;
	t_game game;

	game.mlx = mlx_init();

	int zoom = 55;
	int x =zoom * map->length;
	int y= zoom * map->width;
	//1 - ширина 2 - высота
	game.win = mlx_new_window(game.mlx, y, x, "so_long");
	int width = zoom;
	int length = zoom;
	game.coin_count = 0;
	game.counter = 0;
	game.wall = mlx_xpm_file_to_image(game.mlx, "wall.xpm", &width, &length);
	game.door = mlx_xpm_file_to_image(game.mlx, "door.xpm", &width, &length);
	game.goblin = mlx_xpm_file_to_image(game.mlx, "goblin.xpm", &width, &length);
	game.floor = mlx_xpm_file_to_image(game.mlx, "floor.xpm", &width, &length);
	game.hero = mlx_xpm_file_to_image(game.mlx, "alex.xpm", &width, &length);
	game.coin = mlx_xpm_file_to_image(game.mlx, "coin.xpm", &width, &length);
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
				map->x_hero = x-1;
				map->y_hero = y-1;
			}
			if (map->map[x-1][y-1] == 'C')
			{
				mlx_put_image_to_window(game.mlx, game.win , game.coin, y*zoom - zoom , x*zoom - zoom);
				game.coin_count++;
			}
			if (map->map[x-1][y-1] == 'E')
				mlx_put_image_to_window(game.mlx, game.win , game.door, y*zoom - zoom , x*zoom - zoom);
			}
			x--;
		}
		x = map->length;
		y--;
	}
	// printf("HEEEEKKOOOOOOOOOOOOOO2");
	// mlx_put_image_to_window(game.mlx, game.win , game.goblin, zoom*10 , zoom *10);
	// mlx_hook(game.win, 2, 1L<<0, key_hook_press, &game);
	map->zoom = zoom;
	game.map = map;

	mlx_hook(game.win, 2, 1L<<0, key_hook_press, &game);
	// pri/ntf("HEEEEKKOOOOOOOOOOOOOO3");
	mlx_loop(game.mlx);
	return(0);
}


void process_errors(int error)
{
	if (error)
		exit(0);
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



char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	s_length;
	char	*s_start;
	char	*new_string_start;
	char	*new_string;

	if (s == NULL)
		return (NULL);
	new_string_start = malloc(sizeof(char) * (len + 1));
	if (new_string_start == NULL)
		return (NULL);
	new_string = new_string_start;
	s_length = ft_strlen(s);
	s_start = (char *)s;
	s += start;
	while ((size_t)(s - s_start) < s_length && len--)
		*new_string++ = *s++;
	*new_string = '\0';
	return (new_string_start);
}



static int			count_words(char const *s, char c)
{
	size_t word_count;
	size_t skipper;

	word_count = 0;
	skipper = 1;
	while (*s)
	{
		if (*s != c && skipper)
		{
			skipper = 0;
			word_count++;
		}
		else if (*s++ == c)
			skipper = 1;
	}
	return (word_count);
}

static char	*skip_equal_chars(char *s, char c)
{
	while (*s && *s == c)
		s++;
	return (s);
}

static void			create_words(
	char **words, char *s, char c, size_t word_count)
{
	char *pointerator;

	s = skip_equal_chars(s, c);
	while (word_count--)
	{
		pointerator = ft_strchr(s, c);
		if (pointerator != NULL)
		{
			*words = ft_substr(s, 0, pointerator - s);
			s = skip_equal_chars(pointerator, c);
		}
		else
			*words = ft_substr(s, 0, ft_strlen(s) + 1);
		words++;
	}
	*words = NULL;
}

char				**ft_split(char *s, char c, t_map *map)
{
	size_t	word_count;
	char	**words;

	if (s == NULL)
		return (NULL);
	word_count = count_words(s, c);
	map->length = word_count;
	words = malloc(sizeof(char **) * (word_count + 1));
	if (words == NULL)
		return (NULL);
	create_words(words, s, c, word_count);
	return (words);
}



char    *ft_strjoin2(char *s1, char *s2)
{
    size_t  i;
    size_t  l1;
    size_t  l2;
    char    *str;

    l1 = ft_strlen(s1);
    l2 = ft_strlen(s2);
    str = (char*)malloc(sizeof(char) * (l1 + l2 + 1));
    if (str == 0)
        return (str);
    i = 0;
    while (i < l1)
    {
        str[i] = s1[i];
        ++i;
    }
    i = 0;
    while (i < l2)
    {
        str[l1 + i] = s2[i];
        ++i;
    }
    str[l1 + i] = 0;
    return (str);
}
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
			return(4);
		if (map->map[i][0] != '1')
			return(5);
		if (map->map[i][map->width - 1] != '1')
			return(5);
		i++;
		//printf("%d - %swidth_proverka\n", ft_strlen(map->map[i]), map->map[i]);
	}
	if (ft_consist(map->map[0], '1'))
		return(10);
	if (ft_consist(map->map[len-1], '1'))
		return(7);
	return 0;
}




void build_the_map(char *name_of_the_map, t_map *map)
{
	int error;
	error  = check_the_type_of_map(name_of_the_map);
	char *line;
	int fd = open(name_of_the_map, O_RDONLY);
	if (error)
		process_errors(error);
	map->length = 0;
	char *line_common = NULL;
	while (get_next_line(fd, &line))
	{
		map->width = ft_strlen(line);
		// printf("%d - width\n", map->width);
		// printf("{%d}\n" ,map->width);
		line_common = ft_strjoin2(line_common, line);
		// printf("{%s}\n" ,line_common);
		line_common = ft_strjoin2(line_common, "\n");
	}
	// printf("{%s}\n" ,line_common);
	map->map = ft_split(line_common, '\n', map);
	error = check_borders(map);
	if (error)
	{
		printf("%d - error \n", error);
		process_errors(error);
	}
	printf("{%s}\n" ,map->map[0]);
}



int main(int argc, char **argv)
{
	t_map map;

	if (argc != 2)
		printf("dd\n");
		// process_errors(56);

	build_the_map(argv[1], &map);
	play(&map);
	return (0);
}


// int main()
// {
// 	char *line;
// 	// line = (char*)malloc(1);
// 	int fd;
// 	fd = open("bla_bla.txt", O_RDONLY);
// 	get_next_line(fd, &line);
// 	// printf( "{%s}\n" ,line);
// 	printf("===================");
// 	get_next_line(fd, &line);
// 	// printf( "|%s|\n" ,line);
// 	// get_next_line(fd, &line);
// 	// printf( "|%s|\n" ,line);
// 	// get_next_line(fd, &line);
// 	// printf( "|%s|\n" ,line);
// }
//2 вверх
// 1 вниз
// 17 влево
// вправо
	// Esc = 53,
	// Up = 13,
	// Down = 1,
	// Right = 2,
	// Left = 0,
// Создать карту
// Соорудить стены
// СДелать Невского 
// Сделать Баженова
// Сделать куриные крылья
