/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2025/03/15 18:21:18 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"

static void	default_colours(t_game *g)
{
	if (!g->texture.ceiling)
		g->texture.ceiling = ft_strdup("17,17,132");
	if (!g->texture.floor)
		g->texture.floor = ft_strdup("237,232,208");
}

/*int	quit_game(t_game *game)
{
	if (game->display && game->display->mlx_img)
		mlx_destroy_image(game->mlx_ptr, game->display->mlx_img);
	if (game->win_ptr != NULL)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr != NULL)
	{
		free(game->mlx_ptr);
		game->mlx_ptr = NULL;
	}
	exit(0);
}*/

int	key_handler(const int key, t_game *game)
{
	(void)game;
	if (key == ESC)
	{
		ft_printf("\n'ESC' pressed, game closed...\nThanks for playing!\n");
		destroy_game(game);
	}
	if (key == W)
		ft_printf("Move Up\n");//move_up(game);
	if (key == S)
		ft_printf("Move down\n");//move_down(game);
	if (key == A)
		ft_printf("Move left\n");//move_left(game);
	if (key == D)
		ft_printf("Move right\n");//move_right(game);
	if (key == LEFT)
		ft_printf("Look left\n");//look_direction(game, true);
	if (key == RIGHT)
		ft_printf("Look right\n");//look_direction(game, false);
	return (0);
}

void	ft_get_player_pos(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map->layout[i])
	{
		j = 0;
		while (game->map->layout[i][j])
		{
			if (game->map->layout[i][j] == 'N' || game->map->layout[i][j] == 'S'
				|| game->map->layout[i][j] == 'E' || game->map->layout[i][j] == 'W')
			{
				game->player.player_x = i + 0.5;
				game->player.player_y = j + 0.5;
				set_player_direction(game, game->map->layout[i][j]);
				game->map->layout[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
	destroy_game(game);
}

void	set_player_direction(t_game *game, const char c)
{
	if (c == 'N')
	{
		game->dirx = -1;
		game->plane_y = 0.66;
	}
	else if (c == 'S')
	{
		game->dirx = 1;
		game->plane_y = -0.66;
	}
	else if (c == 'E')
	{
		game->diry = 1;
		game->plane_x = 0.66;
	}
	else if (c == 'W')
	{
		game->diry = -1;
		game->plane_x = -0.66;
	}
}

void	calculate_ray_direction(t_game *game, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIDTH - 1;
	game->ray->raydir_x = game->dirx + game->plane_x * camera_x;
	game->ray->raydir_y = game->diry + game->plane_y * camera_x;
	game->ray->map_x = (int)game->player.player_x;
	game->ray->map_y = (int)game->player.player_y;
	if (game->ray->raydir_x == 0)
		game->ray->deltadist_x = 1e30;
	else
		game->ray->deltadist_x = fabs(1 / game->ray->raydir_x);
	if (game->ray->raydir_y == 0)
		game->ray->deltadist_y = 1e30;
	else
		game->ray->deltadist_y = fabs(1 / game->ray->raydir_y);
}

void	calculate_lines(t_game *game)
{
	int	line_height;

	line_height = (int)(HEIGHT / game->ray->distance);
	game->ray->line_height = line_height;
	game->ray->h_pixel = -line_height / 2 + HEIGHT / 2;
	game->ray->l_pixel = line_height / 2 + HEIGHT / 2;
	if (game->ray->h_pixel < 0)
		game->ray->h_pixel = 0;
	if (game->ray->l_pixel >= HEIGHT)
		game->ray->l_pixel = HEIGHT - 1;
}

void	dda(t_game *game)
{
	bool	wall_hit;

	wall_hit = false;
	while (wall_hit == false)
	{
		if (game->ray->raydist_x < game->ray->raydist_y)
		{
			game->ray->raydist_x += game->ray->deltadist_x;
			game->ray->map_x += game->ray->step_x;
			game->ray->side = false;
		}
		else
		{
			game->ray->raydist_y += game->ray->deltadist_y;
			game->ray->map_y += game->ray->step_y;
			game->ray->side = true;
		}
		if (game->map->layout[game->ray->map_x][game->ray->map_y] == '1')
			wall_hit = true;
	}
	if (game->ray->side == false)
		game->ray->distance = (game->ray->raydist_x - game->ray->deltadist_x);
	else
		game->ray->distance = (game->ray->raydist_y - game->ray->deltadist_y);
}

void	calculate_ray_steps(t_game *game)
{
	if (game->ray->raydir_x < 0)
	{
		game->ray->step_x = -1;
		game->ray->raydist_x = (game->player.player_x - game->ray->map_x) \
		* game->ray->deltadist_x;
	}
	else
	{
		game->ray->step_x = 1;
		game->ray->raydist_x = (game->ray->map_x + 1.0 - game->player.player_x) \
		* game->ray->deltadist_x;
	}
	if (game->ray->raydir_y < 0)
	{
		game->ray->step_y = -1;
		game->ray->raydist_y = (game->player.player_y - game->ray->map_y) \
		* game->ray->deltadist_y;
	}
	else
	{
		game->ray->step_y = 1;
		game->ray->raydist_y = (game->ray->map_y + 1.0 - game->player.player_y) \
		* game->ray->deltadist_y;
	}
}

void	shoot_rays(t_game *game)
{
	int	x;

	x = 0;
	while (x++ < WIDTH - 1)
	{
		calculate_ray_direction(game, x);
		calculate_ray_steps(game);
		dda(game);
		calculate_lines(game);
		draw_floor_ceiling(game, x, game->ray->h_pixel, game->ray->l_pixel);
		draw_wall(game, game->ray->h_pixel, game->ray->l_pixel, x);
	}
}

void	init_game(t_game *game)
{
	display_window(game);
	if (game->win_ptr == NULL)
		return ;
	mlx_loop_hook(game->mlx_ptr, &game_frame_loop, game);
	mlx_hook(game->win_ptr, KeyPress, KeyPressMask, &key_handler, game);
	mlx_hook(game->win_ptr, DestroyNotify, StructureNotifyMask,
		&destroy_game, game);
	mlx_loop(game->mlx_ptr);
}

void	display_window(t_game *game)
{
	if (game->mlx_ptr == NULL)
		return ;
	game->win_ptr = mlx_new_window(game->mlx_ptr,
			WIDTH, HEIGHT, "cub3d");
	if (game->win_ptr == NULL)
		return ;
}

int	game_frame_loop(t_game *game)
{
	if (game->display && game->display->mlx_img)
		mlx_destroy_image(game->mlx_ptr, game->display->mlx_img);
	game->display->mlx_img = mlx_new_image(game->mlx_ptr,
			WIDTH, HEIGHT);
	game->display->addr = mlx_get_data_addr(game->display->mlx_img,
			&game->display->bpp, &game->display->line_len,
			&game->display->endian);
	shoot_rays(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
		game->display->mlx_img, 0, 0);
	return (0);
}

t_game	*strutc_init(t_game *game)
{
	game->ray = (t_ray *)ft_calloc(sizeof(t_ray), 1);
	if (game->ray == NULL)
		return (NULL);
	game->display = ft_calloc(sizeof(t_graph), 1);
	if (game->display == NULL)
		return (NULL);
	ft_get_player_pos(game);
	init_window(game);
	create_all_textures(game);
	return (game);
}


int	main(int argc, char **argv)
{
	t_game	g;
	int		i;

	if (argc != 2)
		return (ft_error_msg("Insert one argument only"));
	if (ft_strlen(argv[1]) < 4
		|| !ft_strnstr(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4))
		return (ft_error_msg("Argument must be a .cub file"));
	ft_bzero(&g, sizeof (t_game));
	load_map(&g, argv[1]);
	default_colours(&g);
	validate_map(&g);
	ft_printf("Floor: %s\nCeiling: %s\n", g.texture.floor, g.texture.ceiling);
	ft_printf("NO: %s\nSO: %s\nWE: %s\nEA: %s\n", g.texture.north, g.texture.south, g.texture.west, g.texture.east);
	i = 0;
	while (g.map->layout[i])
	{
		ft_printf("%s$\n", g.map->layout[i]);
		i++;
	}
	t_game *game_ptr = strutc_init(&g);
	if (game_ptr == NULL)
		return (ft_error_msg("Failed to initialize game structure"));
	g = *game_ptr;
	init_game(&g);
	// load everything else
	// initialise some variables?
	// run game
	destroy_game(&g);
	return (0);
}

/*int	main(int argc, char **argv)
{
	t_game	g;

	if (argc != 2)
		return (error_msg("Insert one argument only"));
	if (ft_strlen(argv[1]) < 4
		|| !ft_strnstr(argv[1] + ft_strlen(argv[1]) - 4, ".ber", 4))
		return (error_msg("Argument must be a .ber file"));
	g.nsprites = 5;
	load_map(&g, argv[1]);
	validate_map(&g);
	load_graphics(&g);
	load_sprites(&g, g.nsprites);
	render_map(&g);
	g.moves = 0;
	g.curr = g.map->pos_player;
	g.next = g.map->pos_player;
	mlx_hook(g.display.win, 2, (1L << 0), move_handler, &g);
	mlx_hook(g.display.win, 17, (1L << 17), &destroy_game, &g);
	mlx_loop_hook(g.display.mlx, render_movement, &g);
	mlx_loop(g.display.mlx);
	return (0);
}*/
