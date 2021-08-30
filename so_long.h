#ifndef SO_LONG_H
# define SO_LONG_H

# include "mlx/mlx.h"
# include <math.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_map
{
	char	**map;
	int		length;
	int		width;
	int		x_hero;
	int		y_hero;
	int		zoom;
}				t_map;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	void	*wall;
	void	*goblin;
	void	*door;
	void	*floor;
	void	*hero;
	void	*coin;
	void	*enemy;
	int		coin_count;
	int		counter;
	int		exit_count;
	int		hero_count;	
	t_map	*map;
}				t_game;

char		**ft_split(char const *s, char c, t_map *map);
char		*ft_substr(char *s, unsigned int start, size_t len);
char		*ft_strjoin2(char *s1, char *s2);
int			ft_strlen(char *str);
int			ft_contains(char *the_word, char the_symbol);
int			ft_consist(char *the_word, char the_symbol);
void		initial_stack_bricks(int x, int y, t_game *g, t_map *map);
void		init_the_game(t_game *g, int width, int length);
int			check_the_type_of_map(char *name_of_the_map);
int			check_borders(t_map *map);
int			start_heroes(t_game *game);
void		print_mass(char **mass);
static void	key_move_step(t_game *game, int x_hero, int y_hero, \
							t_map *m);
int			key_hook_press(int keycode, t_game *g);
int			key_hook_click(int keycode, t_game *game);
void		process_errors_cont(int error);
void		process_errors(int error);
void		stack_bricks(int x, int y, t_game *g, t_map *map);
void		play(t_map *m);
void		read_and_parse(char *line, t_map *map, char **line_common);
void		build_the_map(char *name_of_the_map, t_map *map);
void		stack_bricks_bonus(int x, int y, t_game *g, t_map *map);
void		initial_stack_bricks_bonus(int x, int y, t_game *g, t_map *map);
#endif