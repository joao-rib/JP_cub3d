/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroying.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2025/03/31 12:34:18 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	destroy_textures(t_game *g)
{
	if (g->texture.ceiling)
		free(g->texture.ceiling);
	if (g->texture.floor)
		free(g->texture.floor);
	if (g->texture.north)
		free(g->texture.north);
	if (g->texture.south)
		free(g->texture.south);
	if (g->texture.west)
		free(g->texture.west);
	if (g->texture.east)
		free(g->texture.east);
}

void	destroy_map(t_game *g)
{
	if (!g->map)
		return ;
	g->map->map_size.y--;
	while (g->map->map_size.y >= 0)
	{
		free(g->map->layout[g->map->map_size.y]);
		g->map->map_size.y--;
	}
	free(g->map->layout);
	free(g->map);
	destroy_textures(g);
}

int	destroy_game(t_game *g)
{
	if (!g)
		return (1);
	if (g->ray)
		destroy_ray(g); // WIP
	if (g->display)
		destroy_display(g); // WIP
	//if (g->display.win)
	//	mlx_destroy_window(g->display.mlx, g->display.win);
	//if (g->display.mlx)
	//	mlx_destroy_display(g->display.mlx);
	if (g->map)
		destroy_map(g);
	//free(g->display.mlx);
	exit(1);
	return (1);
}
