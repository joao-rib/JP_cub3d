/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2025/03/15 18:21:02 by joao-rib         ###   ########.fr       */
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
# include "../mlx/minilibx-linux/mlx.h"

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

/*typedef struct s_sprite
{
	int		width;
	int		height;
	void	*img;
}			t_sprite;*/

/*typedef struct s_graph
{
	void	*mlx;
	void	*win;
}			t_graph;*/

typedef struct s_game
{
	struct s_map		*map;
	struct s_texture	texture;
//	struct s_sprite	*sprite;
//	struct s_graph	display;
//	struct s_point	curr;
//	struct s_point	next;
//	int				moves;
//	int				coins;
//	int				nsprites;
//	int				textpos_y;
}			t_game;

//Utils - Error Handling
void	error_exit(char *msg, t_game *g);
void	error_map(char *msg, t_game *g);
//Utils - Destroying
void	destroy_map(t_game *g);
int		destroy_game(t_game *game);
//Utils - Other
void	load_map(t_game *g, char *file);
void	validate_map(t_game *g);
int		flood_fill_cub3d(char **tab, t_game *g, t_point begin);

#endif
