/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/07/11 17:55:14 by joao-rib         ###   ########.fr       */
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

/*typedef struct s_point
{
	int	x;
	int	y;
}		t_point;*/

typedef struct s_map
{
	char			**layout;
	int				map_on_file;
//	int				num_coins;
	struct s_point	map_size;
//	struct s_point	pos_exit;
	struct s_point	pos_player;
}			t_map;

typedef struct s_texture
{
	char	*ceiling;
	char	*floor;
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
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
void	error_exit(char *msg, t_game *g); // WIP pode ser necessário reescrever
void	error_map(char *msg, t_game *g); // WIP pode ser necessário reescrever
//Utils - Loading
void	load_map(t_game *g, char *file);
//void	load_graphics(t_game *g);
//void	load_sprites(t_game *g, int nsprites);
//Utils - Rendering
//void	render_map(t_game *g);
//int		render_movement(t_game *g);
//Utils - Moving
//int		move_handler(int keypress, t_game *g);
//void	move_player(t_game *g);
//Utils - Destroying
void	destroy_map(t_game *g); // WIP pode ser necessário reescrever
int		destroy_game(t_game *game);  // WIP pode ser necessário reescrever
//Utils - Other
void	validate_map(t_game *g);

#endif
