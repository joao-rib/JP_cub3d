/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2025/03/31 14:43:11 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	create_all_textures(t_game *g)
{

}

static int	init_window(t_game *game)
{

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
}

void	load_graphics(t_game *g)
{
	char	*line;
	int		fd;
	int		i;

	set_player_direction(g, g->map->pos_player);
	g->ray = (t_ray *)ft_calloc(sizeof(t_ray), 1);
	if (g->ray == NULL)
		error_exit("Memory allocation error (ray)", g);
	g->display = ft_calloc(sizeof(t_graph), 1);
	if (g->display == NULL)
		error_exit("Memory allocation error (display)", g);
	init_window(g); //WIP
	create_all_textures(g); //WIP
}
