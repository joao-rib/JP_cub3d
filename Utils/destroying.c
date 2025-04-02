/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroying.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2025/04/02 19:28:51 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	destroy_img(t_game *g)
{
	int	i;

	if (!g->texture_img)
		return ;
	i = 0;
	while (i < 4)
	{
		if (g->texture_img[i])
		{
			if (g->texture_img[i]->img)
			{
				mlx_destroy_image(g->mlx_ptr, g->texture_img[i]->img->mlx_img);
				free(g->texture_img[i]->img);
			}
			free(g->texture_img[i]);
		}
		i++;
	}
	free(g->texture_img);
	g->texture_img = NULL;
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

int	destroy_game(t_game *g)
{
	if (!g)
		return (1);
	if (g->ray)
		free(g->ray);
	if (g->texture_img)
		destroy_img(g);
	if (g->display->mlx_img)
		mlx_destroy_image(g->mlx_ptr, g->display->mlx_img);
	if (g->display)
		free(g->display);
	if (g->win_ptr)
		mlx_destroy_window(g->mlx_ptr, g->win_ptr);
	if (g->mlx_ptr)
	{
		mlx_destroy_display(g->mlx_ptr);
		free(g->mlx_ptr);
	}
	if (g->map)
		destroy_map(g);
	exit(1);
	return (1);
}
