/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbezerra <tbezerra@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2025/03/31 15:05:31 by tbezerra         ###   ########.fr       */
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

int	create_texture(t_game *game, const int index, char *path,
	const char *error_msg)
{
	t_text_img	*texture;

	texture = game->texture_img[index];
	texture->img->mlx_img = mlx_xpm_file_to_image(game->mlx_ptr,
			path, &texture->width, &texture->height);
	if (texture->img->mlx_img == NULL)
	{
		printf("\nNo texture created (%s)\n\n", error_msg);
		return (1);
	}
	texture->img->addr = mlx_get_data_addr(texture->img->mlx_img,
			&texture->img->bpp, &texture->img->line_len, &texture->img->endian);
	if (texture->img->addr == NULL)
	{
		printf("\nNo texture addr created (%s)\n\n", error_msg);
		return (1);
	}
	return (0);
}

void	create_all_textures(t_game *game)
{
if (create_texture(game, 0, game->texture.north, "NORTH")
	|| create_texture(game, 1, game->texture.south, "SOUTH")
	|| create_texture(game, 2, game->texture.east, "EAST")
	|| create_texture(game, 3, game->texture.west, "WEST"))
{
	destroy_game(game);
}
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

void	init_window(t_game *game)
{
	int	i;

	i = 0;
	game->mlx_ptr = mlx_init();
	game->win_ptr = NULL;
	game->texture_img = ft_calloc(sizeof(t_text_img *), 4);
	while (i < 4)
	{
		game->texture_img[i] = ft_calloc(1, sizeof(t_text_img));
		game->texture_img[i]->height = 64;
		game->texture_img[i]->width = 64;
		game->texture_img[i]->img = ft_calloc(1, sizeof(t_graph));
		i++;
	}
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
