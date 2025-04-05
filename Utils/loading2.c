/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2025/04/05 12:10:33 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	count_ws(char *line, int start)
{
	while (ft_isdelim(line[start]))
		start++;
	return (start);
}

static int	create_texture(t_game *game, const int index, char *path,
	const char *error_msg)
{
	t_text_img	*texture;

	texture = game->texture_img[index];
	texture->img->mlx_img = mlx_xpm_file_to_image(game->mlx_ptr,
			path, &texture->width, &texture->height);
	if (texture->img->mlx_img == NULL)
	{
		printf("\nNo texture created (%s)\n\n", error_msg);
		free(texture->img);
		free(texture);
		game->texture_img[index] = NULL;
		return (1);
	}
	texture->img->addr = mlx_get_data_addr(texture->img->mlx_img,
			&texture->img->bpp, &texture->img->line_len, &texture->img->endian);
	if (texture->img->addr == NULL)
	{
		printf("\nNo texture addr created (%s)\n\n", error_msg);
		mlx_destroy_image(game->mlx_ptr, texture->img->mlx_img);
		free(texture->img);
		free(texture);
		game->texture_img[index] = NULL;
		return (1);
	}
	return (0);
}

static void	init_window(t_game *game)
{
	int	i;

	i = 0;
	game->mlx_ptr = mlx_init();
	game->win_ptr = NULL;
	game->texture_img = ft_calloc(sizeof(t_text_img *), 4);
	if (game->texture_img == NULL)
		error_exit("Memory allocation error (texture_img)", game);
	while (i < 4)
	{
		game->texture_img[i] = ft_calloc(1, sizeof(t_text_img));
		game->texture_img[i]->height = 64;
		game->texture_img[i]->width = 64;
		game->texture_img[i]->img = ft_calloc(1, sizeof(t_graph));
		i++;
	}
}

static void	set_player_direction(t_game *game, t_point player)
{
	if (game->map->layout[player.y][player.x] == 'N')
	{
		game->dirx = -1;
		game->plane_y = 0.66;
	}
	else if (game->map->layout[player.y][player.x] == 'S')
	{
		game->dirx = 1;
		game->plane_y = -0.66;
	}
	else if (game->map->layout[player.y][player.x] == 'E')
	{
		game->diry = 1;
		game->plane_x = 0.66;
	}
	else if (game->map->layout[player.y][player.x] == 'W')
	{
		game->diry = -1;
		game->plane_x = -0.66;
	}
	game->map->layout[player.y][player.x] = '0';
}

void	load_graphics(t_game *g)
{
	set_player_direction(g, g->map->pos_player);
	g->ray = (t_ray *)ft_calloc(sizeof(t_ray), 1);
	if (g->ray == NULL)
		error_exit("Memory allocation error (ray)", g);
	g->display = ft_calloc(sizeof(t_graph), 1);
	if (g->display == NULL)
		error_exit("Memory allocation error (display)", g);
	init_window(g);
	if (create_texture(g, 0, g->texture.north, "NORTH")
		|| create_texture(g, 1, g->texture.south, "SOUTH")
		|| create_texture(g, 2, g->texture.east, "EAST")
		|| create_texture(g, 3, g->texture.west, "WEST"))
	{
		destroy_game(g);
	}
}
