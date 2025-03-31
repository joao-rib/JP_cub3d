/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2025/03/31 15:52:22 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"

static bool	check_file(char *path)
{
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (false);
	close(fd);
	return (true);
}

static bool	default_colours(t_game *g)
{
	bool	result;

	result = true;
	if (!g->texture.ceiling)
		g->texture.ceiling = ft_strdup("17,17,132");
	if (!g->texture.floor)
		g->texture.floor = ft_strdup("237,232,208");
	if (g->texture.north)
		result = check_file(g->texture.north);
	if (result && g->texture.south)
		result = check_file(g->texture.south);
	if (result && g->texture.west)
		result = check_file(g->texture.west);
	if (result && g->texture.east)
		result = check_file(g->texture.east);
	if (!result)
		destroy_map(g);
	return (result);
}

void	better_mlx_pixel_put(t_graph **img, int x, int y, int color)
{
	char	*dst;

	dst = (*img)->addr + (y * (*img)->line_len + x * ((*img)->bpp / 8));
	*(unsigned int *)dst = color;
}

int	get_pixel_color(t_game *game, int higher_pixel, int lower_pixel, int t_index)
{
	int	color;

	color = *(unsigned int *)(game->texture_img[t_index]->img->addr \
	+ (higher_pixel * game->texture_img[t_index]->img->line_len + lower_pixel \
			* (game->texture_img[t_index]->img->bpp / 8)));
	return (color);
}

void	print_texture_pixel(t_game *game, int x, int h_pixel, int color)
{
	if (game->ray->side == true)
	{
		if (game->ray->raydir_y > 0)
			better_mlx_pixel_put(&game->display, x, h_pixel, color);
		else
			better_mlx_pixel_put(&game->display, x, h_pixel, color);
	}
	else
	{
		if (game->ray->raydir_x > 0)
			better_mlx_pixel_put(&game->display, x, h_pixel, color);
		else
			better_mlx_pixel_put(&game->display, x, h_pixel, color);
	}
}

int	find_right_side(t_game *game, int tex_y, int tex_x)
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

unsigned long	convert_rgb(char *color)
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

void	draw_floor(t_game *game, int x, int ray_count, int l_pixel)
{
	unsigned long	floor_rgb_set;
	unsigned long	floor_rgb;
	int				stop;

	floor_rgb_set = convert_rgb(game->texture.floor);
	stop = (HEIGHT / 2) + ((HEIGHT / 2) / 2);
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

void	draw_ceiling(t_game *game, int x, int ray_count, int h_pixel)
{
	unsigned long	ceiling_rgb;
	unsigned long	ceiling_rgb_set;
	int				stop;

	ceiling_rgb_set = convert_rgb(game->texture.ceiling);
	stop = (HEIGHT / 2) - ((HEIGHT / 2) / 2);
	while (x < HEIGHT / 2)
	{
		if (x == h_pixel)
			return ;
		ceiling_rgb = ceiling_rgb_set;
		if (x > ((HEIGHT / 2) + stop) / 2)
			better_mlx_pixel_put(&game->display, ray_count, x++, 0);
		else if (x >= ((HEIGHT / 2) / 2) - 100)
			better_mlx_pixel_put(&game->display, ray_count, x++, ceiling_rgb);
		else
			better_mlx_pixel_put(&game->display, ray_count, x++, ceiling_rgb_set);
	}
}

void	draw_floor_ceiling(t_game *game, int ray_count, int h_pixel, \
	int l_pixel)
{
	int		x;

	x = 0;
	draw_ceiling(game, x, ray_count, h_pixel);
	x = HEIGHT / 2;
	draw_floor(game, x, ray_count, l_pixel);
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
		print_texture_pixel(game, x, h_pixel, color);
	}
}

static void	init_game(t_game *game)
{
	if (game->mlx_ptr == NULL)
		return ;
	game->win_ptr = mlx_new_window(game->mlx_ptr,
			WIDTH, HEIGHT, "cub3d");
	if (game->win_ptr == NULL)
		return ;
	mlx_loop_hook(game->mlx_ptr, &game_frame_loop, game);
	mlx_hook(game->win_ptr, KeyPress, KeyPressMask, &key_handler, game);
	mlx_hook(game->win_ptr, DestroyNotify, StructureNotifyMask,
		&destroy_game, game);
	mlx_loop(game->mlx_ptr);
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
	if (!default_colours(&g))
		return (ft_error_msg("Texture file not found"));
	validate_map(&g);
	ft_printf("Floor: %s\nCeiling: %s\n", g.texture.floor, g.texture.ceiling);
	ft_printf("NO: %s\nSO: %s\nWE: %s\nEA: %s\n", g.texture.north, g.texture.south, g.texture.west, g.texture.east);
	i = 0;
	while (g.map->layout[i])
	{
		ft_printf("%s$\n", g.map->layout[i]);
		i++;
	}
	load_graphics(&g); //WIP Functions to be written
	init_game(&g); //WIP
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
