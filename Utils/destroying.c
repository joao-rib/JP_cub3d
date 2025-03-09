/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroying.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/07/10 18:28:00 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*void	destroy_map(t_game *g)
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
}

static void	destroy_sprites(t_game *g)
{
	g->nsprites--;
	while (g->nsprites >= 0)
	{
		mlx_destroy_image(g->display.mlx, g->sprite[g->nsprites].img);
		g->nsprites--;
	}
	free(g->sprite);
}

int	destroy_game(t_game *g)
{
	if (!g)
		return (1);
	if (g->sprite)
		destroy_sprites(g);
	if (g->display.win)
		mlx_destroy_window(g->display.mlx, g->display.win);
	if (g->display.mlx)
		mlx_destroy_display(g->display.mlx);
	if (g->map)
		destroy_map(g);
	free(g->display.mlx);
	exit(1);
	return (1);
}*/
