/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2025/03/31 16:50:27 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	get_pixel_color(t_game *g, int h_pixel, int l_pixel, int t_index)
{
	int	color;

	color = *(unsigned int *)(g->texture_img[t_index]->img->addr \
	+ (h_pixel * g->texture_img[t_index]->img->line_len + l_pixel \
			* (g->texture_img[t_index]->img->bpp / 8)));
	return (color);
}

static int	find_right_side(t_game *game, int tex_y, int tex_x)
{
	if (game->ray->side == true)
	{
		if (game->ray->raydir_y > 0)
			return (get_pixel_color(game, tex_y, tex_x, west));
		return (get_pixel_color(game, tex_y, tex_x, east));
	}
	if (game->ray->raydir_x > 0)
		return (get_pixel_color(game, tex_y, tex_x, north));
	return (get_pixel_color(game, tex_y, tex_x, south));
}

int	get_texture_color(t_game *game, int tex_y)
{
	double	wall_x;
	int		tex_x;

	if (game->ray->side == false)
		wall_x = game->player.player_y + game->ray->distance \
			* game->ray->raydir_y;
	else
		wall_x = game->player.player_x + game->ray->distance \
			* game->ray->raydir_x;
	wall_x -= floor(wall_x);
	tex_x = wall_x * (double)TEXTURE_W;
	if (game->ray->side == false && game->ray->raydir_x > 0)
		tex_x = TEXTURE_W - tex_x - 1;
	if (game->ray->side == true && game->ray->raydir_y < 0)
		tex_x = TEXTURE_W - tex_x - 1;
	return (find_right_side(game, tex_y, tex_x));
}
