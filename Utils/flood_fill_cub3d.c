/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_cub3d.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2025/03/15 16:37:20 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	validate_flood(char **tab, t_point size)
{
	t_point	pos;

	pos.y = 0;
	while (pos.y < size.y)
	{
		pos.x = 0;
		while (pos.x < size.x)
		{
			if (!ft_strchr(" F", tab[pos.y][pos.x]))
				return (0);
			pos.x++;
		}
		pos.y++;
	}
	return (1);
}

static int	water_near(char **tab, t_point pos, t_point size)
{
	if (pos.y != 0 && tab[pos.y - 1][pos.x] == 'F')
		return (1);
	if (pos.y != (size.y - 1) && tab[pos.y + 1][pos.x] == 'F')
		return (1);
	if (pos.x != 0 && tab[pos.y][pos.x - 1] == 'F')
		return (1);
	if (pos.x != (size.x - 1) && tab[pos.y][pos.x + 1] == 'F')
		return (1);
	return (0);
}

static int	check_flood(char **tab, t_point pos, t_game *g)
{
	if (ft_strchr("01", tab[pos.y][pos.x])
		&& water_near(tab, pos, g->map->map_size))
	{
		tab[pos.y][pos.x] = 'F';
		return (1);
	}
	return (0);
}

int	flood_fill_cub3d(char **tab, t_game *g, t_point begin)
{
	int		progress;
	t_point	pos;

	tab[begin.y][begin.x] = 'F';
	progress = 1;
	while (progress)
	{
		progress = 0;
		pos.y = 0;
		while (pos.y < g->map->map_size.y)
		{
			pos.x = 0;
			while (pos.x < g->map->map_size.x)
			{
				progress += check_flood(tab, pos, g);
				pos.x++;
			}
			pos.y++;
		}
	}
	progress = validate_flood(tab, g->map->map_size);
	ft_free_matrix(tab);
	return (progress);
}
