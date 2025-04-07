/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbezerra <tbezerra@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2025/04/07 17:51:45 by tbezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <time.h>
# include <errno.h>
# include <math.h>
# include "../libft/libft.h"
# include "./mlx/minilibx-linux/mlx.h"

# include <X11/X.h>
# include <X11/keysym.h>
# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define C 99
# define V 118
# define RIGHT 65363
# define LEFT 65361

# define FOV 60
# define WIDTH 1500
# define HEIGHT 1000
# define BLOCK_SIZE 64
# define PLAYER_SPEED 0.2
# define SCREEN_SENS 0.045
# define TEXTURE_W 64
# define TEXTURE_H 64

typedef enum s_compass
{
	north,
	south,
	east,
	west,
}		t_compass;

typedef struct s_player
{
	double		player_x;
	double		player_y;
}		t_player;

typedef struct s_map
{
	char			**layout;
	int				map_on_file;
	struct s_point	map_size;
	struct s_point	pos_player;
}			t_map;

typedef struct s_texture
{
	char	*ceiling;
	char	*floor;
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}			t_texture;

typedef struct s_text_img
{
	struct s_graph	*img;
	int				width;
	int				height;
}			t_text_img;

typedef struct s_ray
{
	double	ray_angle;
	double	distance;
	int		line_height;
	bool	wall_hit;
	bool	side;

	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	raydir_x;
	double	raydir_y;
	double	raydist_x;
	double	raydist_y;
	double	deltadist_x;
	double	deltadist_y;

	int		l_pixel;
	int		h_pixel;
}	t_ray;

typedef struct s_graph
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_graph;

typedef struct s_game
{
	struct s_map		*map;
	struct s_texture	texture;
	struct s_graph		*display;
	struct s_ray		*ray;
	struct s_player		player;
	struct s_text_img	**texture_img;

	void				*mlx_ptr;
	void				*win_ptr;

	double				dirx;
	double				diry;
	double				plane_x;
	double				plane_y;
}			t_game;

//Utils - Error Handling
void	error_exit(char *msg, t_game *g);
void	error_map(char *msg, t_game *g, bool fd_error);
//Utils - Destroying
void	destroy_map(t_game *g);
int		destroy_game(t_game *game);
//Utils - Loading
void	load_map(t_game *g, char *file);
void	load_graphics(t_game *g);
int		count_ws(char *line, int start);
//Utils - Rendering
int		game_frame_loop(t_game *game);
void	draw_wall(t_game *game, int h_pixel, int l_pixel, int x);
void	draw_ceiling(t_game *game, int x, int ray_count, int h_pixel);
void	draw_floor(t_game *game, int x, int ray_count, int l_pixel);
int		get_texture_color(t_game *game, int tex_y);
//Utils - Moving
int		key_handler(const int key, t_game *game);
void	look_direction(t_game *game, const bool is_left);
//Utils - Validation
void	validate_map(t_game *g);
int		flood_fill_cub3d(char **tab, t_game *g, t_point begin);

#endif
