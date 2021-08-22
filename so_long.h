#ifndef SO_LONG_H
# define SO_LONG_H

# include "mlx/mlx.h"
# include <math.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>


typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;


void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
// {
// 	char	*dst;

// 	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
// 	*(unsigned int*)dst = color;
// }


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
	int exit_count;
	int hero_count;
	t_map *map;

}				t_game;


char	**ft_split(char const *s, char c, t_map *map);
char	*ft_substr(char *s, unsigned int start, size_t len);
char    *ft_strjoin2(char *s1, char *s2);
int	ft_strlen(char *str);

#endif