/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroying.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbezerra <tbezerra@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2025/04/02 17:05:16 by tbezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	destroy_img(t_game *g)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (g->texture_img[i] && g->texture_img[i]->img)
		{
			mlx_destroy_image(g->mlx_ptr, g->texture_img[i]->img); // Libera a imagem
			free(g->texture_img[i]); 
		}
/* 			free(g->texture_img[i]->img); //WIP Verificar addr (valgrind)
		free(g->texture_img[i]); */
		i++;
	}
	free(g->texture_img);
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
	if (g->display)
		free(g->display);
/* 	{
		if (g->display->addr)
			free(g->display->addr);
		free(g->display);
	} */
	if (g->win_ptr)
		mlx_destroy_window(g->mlx_ptr, g->win_ptr);
	if (g->mlx_ptr)
		mlx_destroy_display(g->mlx_ptr);
	if (g->texture_img)
		destroy_img(g);
	if (g->map)
		destroy_map(g);
	exit(1);
	return (1);
}
