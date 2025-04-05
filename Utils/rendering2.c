/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbezerra <tbezerra@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2025/04/05 12:40:57 by tbezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static unsigned long	convert_rgb(char *color)
{
	int		r;
	int		g;
	int		b;
	int		i;
	char	**temp_color;

	i = 0;
	temp_color = ft_split(color, ',');
	if (temp_color)
	{
		if (temp_color[0] && temp_color[1] && temp_color[2])
		{
			r = ft_atoi(temp_color[0]);
			g = ft_atoi(temp_color[1]);
			b = ft_atoi(temp_color[2]);
		}
		else
			return (ft_printf("Error with convert_rgb!\n"));
		while (temp_color[i])
			free(temp_color[i++]);
		free(temp_color);
		return ((r << 16) | (g << 8) | b);
	}
	return (0);
}

static void	better_mlx_pixel_put(t_graph **img, int x, int y, int color)
{
	char	*dst;

	dst = (*img)->addr + (y * (*img)->line_len + x * ((*img)->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_floor(t_game *game, int x, int ray_count, int l_pixel)
{
	unsigned long	floor_rgb_set;
	unsigned long	floor_rgb;
	int				stop;

	floor_rgb_set = convert_rgb(game->texture.floor);
	stop = (HEIGHT / 2) + ((HEIGHT / 2) / 8);
	while (x < HEIGHT)
	{
		while (x < l_pixel)
			x++ ;
		floor_rgb = floor_rgb_set;
		if (x < (((HEIGHT / 2) + stop) / 2))
			better_mlx_pixel_put(&game->display, ray_count, x++, 0);
		else if (x < stop + 50)
			better_mlx_pixel_put(&game->display, ray_count, x++, floor_rgb);
		else
			better_mlx_pixel_put(&game->display, ray_count, x++, floor_rgb_set);
	}
}

void	draw_ceiling(t_game *g, int x, int ray_count, int h_pixel)
{
	unsigned long	ceiling_rgb;
	unsigned long	ceiling_rgb_set;
	int				stop;

	ceiling_rgb_set = convert_rgb(g->texture.ceiling);
	stop = (HEIGHT / 2) - ((HEIGHT / 2) / 2);
	while (x < HEIGHT / 2)
	{
		if (x == h_pixel)
			return ;
		ceiling_rgb = ceiling_rgb_set;
		if (x > ((HEIGHT / 2) + stop))
			better_mlx_pixel_put(&g->display, ray_count, x++, 0);
		else if (x >= ((HEIGHT / 2) / 2) - 100)
			better_mlx_pixel_put(&g->display, ray_count, x++, ceiling_rgb);
		else
			better_mlx_pixel_put(&g->display, ray_count, x++, ceiling_rgb_set);
	}
}

void	draw_wall(t_game *game, int h_pixel, int l_pixel, int x)
{
	double	tex_pos;
	double	step;
	int		color;
	int		tex_y;

	step = 1.0 * TEXTURE_H / game->ray->line_height;
	tex_pos = (h_pixel - HEIGHT / 2 + game->ray->line_height / 2) * step;
	while (h_pixel++ < l_pixel)
	{
		tex_y = (int)tex_pos & (TEXTURE_H - 1);
		tex_pos += step;
		color = get_texture_color(game, tex_y);
		better_mlx_pixel_put(&game->display, x, h_pixel, color);
	}
}
