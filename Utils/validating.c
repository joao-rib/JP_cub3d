/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validating.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbezerra <tbezerra@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2025/04/07 17:57:04 by tbezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static bool	validate_walls2(char **layout, t_point size)
{
	int		i;
	int		j;

	i = 1;
	while (i < (size.y - 1))
	{
		j = 1;
		while (j < (size.x - 1))
		{
			if (!ft_strchr("0NSWE", layout[i][j]))
				;
			else if (layout[i][j - 1] == ' ' || layout[i][j + 1] == ' '
					|| layout[i - 1][j] == ' ' || layout[i + 1][j] == ' ')
				return (false);
			else if (layout[i + 1][j - 1] == ' ' || layout[i + 1][j + 1] == ' ')
				return (false);
			else if (layout[i - 1][j - 1] == ' ' || layout[i - 1][j + 1] == ' ')
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

static bool	validate_walls1(char **layout, t_point size)
{
	int	col;
	int	row;

	col = 0;
	row = 0;
	while (layout[0][col] && ft_strchr(" 1", layout[0][col]))
		col++;
	if (layout[0][col])
		return (false);
	col = 0;
	while (layout[size.y - 1][col] && ft_strchr(" 1", layout[size.y - 1][col]))
		col++;
	if (layout[size.y - 1][col])
		return (false);
	while (row < size.y)
	{
		if (!ft_strchr("1 ", layout[row][0])
			|| !ft_strchr(" 1", layout[row][size.x - 1]))
			return (false);
		row++;
	}
	return (true);
}

static bool	validate_chars(t_game *g)
{
	t_point	pos;

	pos.y = 1;
	while (pos.y < g->map->map_size.y)
	{
		pos.x = 1;
		while (g->map->layout[pos.y][pos.x])
		{
			if (ft_strchr("01 ", g->map->layout[pos.y][pos.x]))
				pos.x *= 1;
			else if (ft_strchr("NSEW", g->map->layout[pos.y][pos.x]))
				g->map->pos_player = pos;
			else
				return (false);
			pos.x++;
		}
		pos.y++;
	}
	return (true);
}

static bool	validate_player(char **layout, t_point size)
{
	int	c;
	int	r;
	int	p;

	p = 0;
	r = 1;
	while (r < size.y)
	{
		c = 1;
		while (layout[r][c])
		{
			if (ft_strchr("NSEW", layout[r][c]))
				p++;
			c++;
		}
		r++;
	}
	if (p == 1)
		return (true);
	else
		return (false);
}

void	validate_map(t_game *g)
{
	if (g->map->map_size.y == 0)
		error_map("Map is empty", g, 0);
	if (!validate_player(g->map->layout, g->map->map_size))
		error_map("Map must have one player", g, 0);
	if (!validate_chars(g))
		error_map("Map has unknown entities", g, 0);
	if (!validate_walls1(g->map->layout, g->map->map_size))
		error_map("Map is not walled", g, 0);
	if (!validate_walls2(g->map->layout, g->map->map_size))
		error_map("Map is not walled", g, 0);
	if (!flood_fill_cub3d(ft_matrix_dup(g->map->layout), g, g->map->pos_player))
		error_map("Map is not contiguous", g, 0);
	g->player.player_y = (double)g->map->pos_player.x + 0.5;
	g->player.player_x = (double)g->map->pos_player.y + 0.5;
}
