/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbezerra <tbezerra@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2025/04/07 17:57:26 by tbezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	calculate_ray_direction(t_game *game, int x)
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

static void	calculate_lines(t_game *game)
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

static void	dda(t_game *game)
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

static void	calculate_ray_steps(t_game *game)
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

int	game_frame_loop(t_game *game)
{
	int	x;

	if (game->display && game->display->mlx_img)
		mlx_destroy_image(game->mlx_ptr, game->display->mlx_img);
	game->display->mlx_img = mlx_new_image(game->mlx_ptr,
			WIDTH, HEIGHT);
	game->display->addr = mlx_get_data_addr(game->display->mlx_img,
			&game->display->bpp, &game->display->line_len,
			&game->display->endian);
	x = 0;
	while (x++ < WIDTH - 1)
	{
		calculate_ray_direction(game, x);
		calculate_ray_steps(game);
		dda(game);
		calculate_lines(game);
		draw_ceiling(game, 0, x, game->ray->h_pixel + 100);
		draw_floor(game, HEIGHT / 2, x, game->ray->l_pixel);
		draw_wall(game, game->ray->h_pixel, game->ray->l_pixel, x);
	}
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
		game->display->mlx_img, 0, 0);
	return (0);
}
