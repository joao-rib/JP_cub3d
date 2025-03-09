/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/07/10 15:53:45 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*static bool	validate_path(t_game *g)
{
	char	**buff;
	bool	resp;
	int		i;

	i = 0;
	resp = false;
	buff = ft_strarrdup(g->map->layout);
	if (!buff)
		return (resp);
	flood_fill_sl(buff, g, g->map->pos_player);
	if (buff[g->map->pos_exit.y][g->map->pos_exit.x + 1] == 'F'
		|| buff[g->map->pos_exit.y][g->map->pos_exit.x - 1] == 'F'
		|| buff[g->map->pos_exit.y + 1][g->map->pos_exit.x] == 'F'
		|| buff[g->map->pos_exit.y - 1][g->map->pos_exit.x] == 'F')
		resp = true;
	if (g->coins != g->map->num_coins)
		resp = false;
	while (buff[i] != NULL)
	{
		free(buff[i]);
		i++;
	}
	free(buff);
	return (resp);
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
			if (g->map->layout[pos.y][pos.x] == 'E')
				g->map->pos_exit = pos;
			else if (g->map->layout[pos.y][pos.x] == 'P')
				g->map->pos_player = pos;
			else if (g->map->layout[pos.y][pos.x] == 'C')
				g->map->num_coins++;
			else if (ft_strchr("01", g->map->layout[pos.y][pos.x]))
				pos.x *= 1;
			else
				return (false);
			pos.x++;
		}
		pos.y++;
	}
	return (true);
}

static bool	validate_ends(char **layout, t_point size)
{
	int	c;
	int	r;
	int	e;
	int	p;

	e = 0;
	p = 0;
	r = 1;
	while (r < size.y)
	{
		c = 1;
		while (layout[r][c])
		{
			if (layout[r][c] == 'E')
				e++;
			else if (layout[r][c] == 'P')
				p++;
			c++;
		}
		r++;
	}
	if (e == 1 && p == 1)
		return (true);
	else
		return (false);
}

static bool	validate_walls(char **layout, t_point size)
{
	int	col;
	int	row;

	col = 0;
	row = 0;
	while (col < size.x)
	{
		if (layout[0][col] != '1' || layout[size.y - 1][col] != '1')
			return (false);
		col++;
	}
	while (row < size.y)
	{
		if (layout[row][0] != '1' || layout[row][size.x - 1] != '1')
			return (false);
		row++;
	}
	return (true);
}*/

void	validate_map(t_game *g)
{
	if (g->map->map_size.y == 0)
		error_map("Map is empty", g);
	if (!validate_walls(g->map->layout, g->map->map_size)) // WIP reescrever, mapa não é quadrado
		error_map("Map is not walled", g);
	if (!validate_ends(g->map->layout, g->map->map_size)) // WIP reescrever, não precisa de exits
		error_map("Map must have one player and one exit", g);
	if (!validate_chars(g)) // WIP reverificar, player tem de ser único
		error_map("Map has unknown entities", g);
	//if (!validate_path(g))
	//	error_map("Map cannot be cleared", g);
}
